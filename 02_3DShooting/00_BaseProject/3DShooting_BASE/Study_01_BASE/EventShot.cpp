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
	// ���e���̃G�t�F�N�g
	mExplosion->Update();

	if (!IsAlive())
	{
		return;
	}

	// �ړ�����
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

	// ���f������̊�{���X�V
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
