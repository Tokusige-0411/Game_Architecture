#include <DxLib.h>
#include "SpriteAnimator.h"
#include "EventShot.h"
#include "SceneManager.h"
#include "Camera.h"

EventShot::EventShot(SceneManager* manager, Transform* parent):ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
	// 着弾時のエフェクト
	mExplosion->Update();

	if (!IsAlive())
	{
		return;
	}

	// 移動処理
	Move();

	VECTOR pos2D = ConvWorldPosToScreenPos(mTransform.pos);
	if (pos2D.z <= 0.0f || pos2D.z >= 1.0f)
	{
		VECTOR vel = VScale(VScale(mDir, -1.0f), 100.0f);
		mTransform.pos = VAdd(mTransform.pos, vel);
		mTransform.Update();

		CreateExplosion();

		mSceneManager->GetCamera()->ChangeMode(Camera::MODE::SHAKE);
	}

	// モデル制御の基本情報更新
	mTransform.Update();
}

float EventShot::GetSpeed(void)
{
	return 20.0f;
}

float EventShot::GetTimeAlive(void)
{
	return 10.0f;
}
