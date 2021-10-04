#include "RollBall.h"
#include "SceneManager.h"
#include "Charactor.h"
#include "AsoUtility.h"

RollBall::RollBall(SceneManager* manager, Charactor* chara)
{
	Init();
	mSceneManager = manager;
	chara_ = chara;
}

RollBall::~RollBall()
{
}

void RollBall::Init(void)
{
	pos_ = { 0.0f, 100.0f, 0.0f };
	localAngles_ = { 0.0f, 180.0f, 0.0f };
	delta_ = 0.0f;
}

void RollBall::Update(void)
{
	delta_ += mSceneManager->GetDeltaTime();

	auto mPos = chara_->GetPos();
	auto rad = 100.0f;

	pos_.x = mPos.x + rad * sinf(delta_ * 1.5f);
	pos_.z = mPos.z + rad * cosf(delta_ * 1.5f);

	zRad_ = chara_->GetAngles().y;
	zRad_ += atan2f(pos_.x - mPos.x, pos_.z - mPos.z);
}

void RollBall::Draw(void)
{
	DrawSphere3D(pos_, 30, 10, 0xffffff, 0xffffff, true);

	auto mPos = chara_->GetPos();

	DrawString(0, 0, "■ボール", 0xffffff);

	zRad_ = atan2f(pos_.x - mPos.x, pos_.z - mPos.z);
	DrawFormatString(0, 15, 0xffffff, "Zの正方向：%f", AsoUtility::Rad2DegF(zRad_));

	zRad_ -= chara_->GetAngles().y;
	DrawFormatString(0, 30, 0xffffff, "プレイヤー基準のZの正方向：%f", AsoUtility::DegIn360(AsoUtility::Rad2DegF(zRad_)));
}
