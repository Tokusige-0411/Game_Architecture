#include "DxLib.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Transform.h"
#include "SpriteAnimator.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Turret.h"
#include "TurretShot.h"

Turret::Turret(SceneManager* manager,
	Transform* transformPlayer,
	Transform* transformParent,
	VECTOR localPos,
	VECTOR localAddAxis)
{

	mSceneManager = manager;
	mTransformPlayer = transformPlayer;

	mTransformParent = transformParent;
	mLocalPos = localPos;
	mLocalAddAxis = localAddAxis;

	ResourceManager* rem = mSceneManager->GetResource();

	mTransformStand.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_STAND));
	mTransformGun.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_GUN));

	mExplosion = new SpriteAnimator(
		mSceneManager, ResourceManager::SRC::SHIP_EXPLOSION, 120, 8.0f);

	mStepDamaged = -1;

	// –Cgƒ[ƒJƒ‹‰ñ“]
	mLocalAddAxisGun = { 0.0f, 0.0f, 0.0f };

	ChangeState(STATE::ATTACK);

}

void Turret::Init(void)
{

	Quaternion localRot;
	Quaternion axis;

	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ(–C‘ä)
	mTransformStand.scl = { SCALE, SCALE, SCALE };
	mTransformStand.quaRot = Quaternion();

	// ƒ[ƒJƒ‹‰ñ“]
	mTransformStand.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// eƒ‚ƒfƒ‹‚Æ“¯Šú
	SyncParent(&mTransformStand, { 0, 0, 0 });



	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ(–Cg)
	mTransformGun.scl = { SCALE, SCALE, SCALE };
	mTransformGun.quaRot = Quaternion();

	// ƒ[ƒJƒ‹‰ñ“]
	mTransformGun.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(-5.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// eƒ‚ƒfƒ‹‚Æ“¯Šú
	SyncParent(&mTransformGun, { 0, 0, 0 });

	// ‘Ï‹v—Í
	mHp = 2;

	// –C‘äƒ[ƒJƒ‹‰Ò“­—Ê(deg)
	mAnglePowStand = ANGLE_POW_STAND;

	// –Cgƒ[ƒJƒ‹‰Ò“­—Ê(deg)
	mAnglePowGun = ANGLE_POW_GUN;

}

void Turret::Update(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
	{

		float deg;

		// –C‘äƒ[ƒJƒ‹‰ñ“]

		// –C‘ä
		mLocalAddAxisStand.y += (mAnglePowStand * mSceneManager->GetDeltaTime());
		deg = AsoUtility::Rad2DegF(mLocalAddAxisStand.y);
		if (deg < ANGLE_Y_MIN_STAND || deg > ANGLE_Y_MAX_STAND)
		{
			mAnglePowStand *= -1.0f;
		}
		SyncParent(&mTransformStand, mLocalAddAxisStand);

		// –Cgƒ[ƒJƒ‹‰ñ“]
		

		// –Cg
		mLocalAddAxisGun.x += (mAnglePowGun * mSceneManager->GetDeltaTime());
		deg = AsoUtility::Rad2DegF(mLocalAddAxisGun.x);
		if (deg < ANGLE_X_MIN_GUN || deg > ANGLE_X_MAX_GUN)
		{
			mAnglePowGun *= -1.0f;
		}
		Quaternion stand = Quaternion::Euler(mLocalAddAxisStand);
		Quaternion gun = Quaternion::Euler(mLocalAddAxisGun);
		Quaternion mix = stand.Mult(gun);
		SyncParent(&mTransformGun, mix.ToEuler());

		// ”íƒ_ƒ”»’è
		if (mStepDamaged > 0.0f)
		{
			mStepDamaged -= mSceneManager->GetDeltaTime();
		}

		ProcessShot();
	}
		break;
	case Turret::STATE::DESTROY:

		// ’e‚ÌXV
		mExplosion->Update();
		break;
	}

}

void Turret::Draw(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:

		if (mStepDamaged > 0.0f)
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
		}
		else
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.48f, 0.52f, 0.4f, 1.0f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.2f, 0.4f, 0.3f, 1.0f));
		}

		MV1DrawModel(mTransformStand.modelId);
		MV1DrawModel(mTransformGun.modelId);

		if (IS_DEBUG)
		{
			DrawSphere3D(mTransformStand.pos, COLLISION_RADIUS, 10, 0xff0000, 0xffffff, false);
		}

		break;
	case Turret::STATE::DESTROY:
		mExplosion->Draw();
		break;
	}

}

void Turret::Release(void)
{

	mExplosion->Release();
	delete mExplosion;

}

void Turret::SyncParent(Transform* transform, VECTOR addAxis)
{
	VECTOR localPos;

	transform->quaRot = mTransformParent->quaRot;

	localPos = Quaternion::PosAxis(transform->quaRot, mLocalPos);
	transform->pos = VAdd(mTransformParent->pos, VScale(localPos, SCALE));

	Quaternion localRot;
	Quaternion axis;

	axis = Quaternion::AngleAxis(mLocalAddAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(mLocalAddAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);



	axis = Quaternion::AngleAxis(addAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	transform->quaRot = transform->quaRot.Mult(localRot);

	transform->Update();
}

bool Turret::IsAlive(void)
{
	return mState == STATE::ATTACK;
}

VECTOR Turret::GetPos(void)
{
	return mTransformStand.pos;
}

void Turret::Damage(void)
{

	mStepDamaged = TIME_DAMAGED_EFFECT;

	mHp -= 1;
	if (mHp <= 0)
	{
		ChangeState(STATE::DESTROY);
	}

}

std::vector<TurretShot*> Turret::GetShot(void)
{
	return shots_;
}

void Turret::ProcessShot(void)
{
	deleyShot_ -= mSceneManager->GetDeltaTime();
	if (deleyShot_ <= 0.0f)
	{
		deleyShot_ = 0.0f;
	}

	if (deleyShot_ <= 0.0f)
	{
		deleyShot_ = shot_delay_time;

		CreateShot();
	}
}

void Turret::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
		break;
	case Turret::STATE::DESTROY:
	{
		auto mat = mTransformGun.quaRot.ToMatrix();
		auto localPos = VTransform({ 0.0f, 1.2f, 0.0f }, mat);
		auto birthPos = VAdd(mTransformStand.pos, VScale(localPos, SCALE));
		mExplosion->Create(birthPos);
	}
	break;
	}

}

void Turret::CreateShot(void)
{
	VECTOR localPos = Quaternion::PosAxis(mTransformGun.quaRot, {0.0f, 2.0f, 3.0f});
	VECTOR pos = VAdd(mTransformGun.pos, VScale(localPos, SCALE));

	VECTOR dir = mTransformGun.GetForward();

	bool isCreate = false;
	for (auto s :shots_)
	{
		if (!(s->IsAlive()))
		{
			s->Create(pos, dir);
			isCreate = true;
		}
	}

	if (!isCreate)
	{
		TurretShot* t = new TurretShot(mSceneManager, &mTransformGun);
		t->Create(pos, dir);
		shots_.emplace_back(t);
	}
}
