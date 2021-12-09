#include "DxLib.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "GameCommon.h"
#include "Camera.h"
#include "Transform.h"

namespace
{
	constexpr float moveSpeed = 30.0f;
	constexpr float rotSpeed = 2.0f;
	constexpr float powSpring = 24.0f;
	constexpr float shake_time = 2.0f;
	constexpr float width_shake = 3.0f;
	constexpr float shake_speed = 30.0f;
}

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
}

Camera::~Camera()
{
}

void Camera::Init()
{
	//ChangeMode(MODE::FOLLOW);
}

void Camera::SetDefault(void)
{

	// カメラの初期設定
	mPos = DEFAULT_CAMERA_POS;
	mTargetPos = VAdd(mPos, RELATIVE_TARGET_POS);
	mCameraUp = { 0.0f, 1.0f, 0.0f };

	// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
	// mQuaRotは回転計算用で、
	// あくまで軸となるのは、カメラ座標と注視点とする
	mQuaRot = Quaternion();

}

void Camera::Update()
{
	// カメラの方向移動と回転
	VECTOR moveDir_ = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_W)) { moveDir_ = AsoUtility::DIR_F; };
	if (CheckHitKey(KEY_INPUT_A)) { moveDir_ = AsoUtility::DIR_L; };
	if (CheckHitKey(KEY_INPUT_S)) { moveDir_ = AsoUtility::DIR_B; };
	if (CheckHitKey(KEY_INPUT_D)) { moveDir_ = AsoUtility::DIR_R; };

	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_UP)) { axisDeg.x -= 1.0f; };
	if (CheckHitKey(KEY_INPUT_DOWN)) { axisDeg.x += 1.0f; };
	if (CheckHitKey(KEY_INPUT_LEFT)) { axisDeg.y -= 1.0f; };
	if (CheckHitKey(KEY_INPUT_RIGHT)) { axisDeg.y += 1.0f; };

	if (!AsoUtility::EqualsVZero(axisDeg))
	{
		VECTOR axisRad;
		axisRad.x= AsoUtility::Deg2RadF(axisDeg.x);
		axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
		axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

		Quaternion axis = Quaternion::Euler(axisRad);
		mQuaRot = mQuaRot.Mult(axis);

		VECTOR localAxis = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
		mTargetPos = VAdd(mPos, localAxis);

		mCameraUp = mQuaRot.GetUp();
	}

	if (!AsoUtility::EqualsVZero(moveDir_))
	{
		MATRIX mat = mQuaRot.ToMatrix();
		VECTOR dir = VNorm(VTransform(moveDir_, mat));

		VECTOR moveVel = VScale(dir, moveSpeed);

		mPos = VAdd(moveVel, mPos);
		mTargetPos = VAdd(moveVel, mTargetPos);
	}
}

void Camera::SetBeforeDraw(void)
{

	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(30.0f, 15000.0f);

	switch (mMode)
	{
	case Camera::MODE::FREE:
		SetBeforeDrawFree();
		break;
	case Camera::MODE::FIXED:
		SetBeforeDrawFixed();
		break;
	case Camera::MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	case Camera::MODE::FOLLOW_SPRING:
		SetBeforeDrawFollowSpring();
		break;
	case Camera::MODE::SHAKE:
		SetBeforeDrawShake();
		break;
	default:
		break;
	}

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		mPos,
		mTargetPos,
		mCameraUp
	);

}

void Camera::SetBeforeDrawFree(void)
{





}

void Camera::SetBeforeDrawFixed(void)
{
	int a = 0;
}

void Camera::SetBeforeDrawFollow(void)
{
	// ﾌﾟﾚｲﾔｰの座標と向き
	VECTOR shipPos = shipTransform_->pos;
	Quaternion shipRot = shipTransform_->quaRot;

	//auto local = VTransform(RELATIVE_CAMERA_FOLLOW, shipTransform_->matRot);
	auto pos = shipRot.PosAxis(RELATIVE_CAMERA_FOLLOW);
	mPos = VAdd(shipPos, pos);

	auto target = shipRot.PosAxis(RELATIVE_TARGET_POS);
	mTargetPos = VAdd(mPos, target);

	mCameraUp = shipRot.GetUp();
}

void Camera::SetBeforeDrawFollowSpring(void)
{
	VECTOR shipPos = shipTransform_->pos;
	Quaternion shipRot = shipTransform_->quaRot;

	VECTOR pos = shipRot.PosAxis(RELATIVE_CAMERA_SPRING);

	float dampening = 2.0f * sqrt(powSpring);
	float delta = mSceneManager->GetDeltaTime();

	VECTOR idealPos = VAdd(shipPos, pos);
	VECTOR diff = VSub(mPos, idealPos);

	VECTOR force;
	force = VScale(diff, -powSpring);
	force = VSub(force, VScale(mVelocity, dampening));

	mVelocity = VAdd(mVelocity, VScale(force, delta));

	mPos = VAdd(mPos, VScale(mVelocity, delta));

	auto target = shipRot.PosAxis(RELATIVE_TARGET_POS);
	mTargetPos = VAdd(mPos, target);

	mCameraUp = shipRot.GetUp();
}

void Camera::SetBeforeDrawShake(void)
{
	stepShake_ -= mSceneManager->GetDeltaTime();

	if (stepShake_ < 0.0f)
	{
		mPos = defaultPos;
		ChangeMode(MODE::FIXED);
		return;
	}

	float pow = width_shake * sinf(stepShake_ * shake_speed);
	auto vel = VScale(shakeDir_, pow);
	mPos = VAdd(defaultPos, vel);
}

void Camera::Draw()
{
}

void Camera::DrawDebug(void)
{
}

void Camera::DrawUI(void)
{

	// 操作説明
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "　【操作】", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　旋回：↑↓←→", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　加速：Ｂ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　発弾：Ｎ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　シーン遷移：Ｓｐａｃｅ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　1500m以上離れると", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "　ゲームオーバー", 0xffffff);

}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}

VECTOR Camera::GetDir(void)
{
	return VNorm(VSub(mTargetPos, mPos));
}

void Camera::ChangeMode(MODE mode)
{
	SetDefault();
	mMode = mode;
	switch (mMode)
	{
	case Camera::MODE::FREE:
		break;
	case Camera::MODE::FIXED:
		break;
	case Camera::MODE::FOLLOW:
		break;
	case Camera::MODE::FOLLOW_SPRING:
		break;
	case Camera::MODE::SHAKE:
		stepShake_ = shake_time;
		shakeDir_ = VNorm({0.7f, 0.7f, 0.7});
		defaultPos = mPos;
		break;
	default:
		break;
	}
}

void Camera::SetShip(Transform* ship)
{
	shipTransform_ = ship;
}
