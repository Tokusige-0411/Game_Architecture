#include "BattleScene.h"
#include "SceneManager.h"
#include "GoldShip.h"
#include "BossShip.h"
#include "RovckManager.h"
#include "SpaceDome.h"
#include "Camera.h"
#include "PlayerShot.h"
#include "Turret.h"
#include "TurretShot.h"
#include "AsoUtility.h"

BattleScene::BattleScene(SceneManager* manager):SceneBase(manager)
{
}

void BattleScene::Init(void)
{
	playerShip_ = new GoldShip(mSceneManager);
	playerShip_->Init();

	spaceDome_ = new SpaceDome(mSceneManager, playerShip_->GetTransform());
	spaceDome_->Init();

	//rockManager_ = new RockManager();
	//rockManager_->Init(mSceneManager, playerShip_->GetTransform());

	bossShip_ = new BossShip(mSceneManager, playerShip_);
	bossShip_->Init();

	auto camera = mSceneManager->GetCamera();
	camera->SetShip(playerShip_->GetTransform());
	camera->ChangeMode(Camera::MODE::FOLLOW_SPRING);
}

void BattleScene::Update(void)
{
	playerShip_->Update();
	spaceDome_->Update();
	//rockManager_->Update();
	bossShip_->Update();

	if (!playerShip_->IsDestoy())
	{
		if (playerShip_->GetState() != PlayerState::Destroy)
		{
			auto info = MV1CollCheck_Sphere(bossShip_->GetTransform().modelId, -1, playerShip_->GetTransform()->pos, GoldShip::COLLISION_RADIUS);
			if (info.HitNum)
			{
				playerShip_->ChangeState(PlayerState::Destroy);
				mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
			}
			MV1CollResultPolyDimTerminate(info);

			auto turrets = bossShip_->GetTurrets();
			for (auto t : turrets)
			{
				auto ts = t->GetShot();
				for (auto s : ts)
				{
					if (AsoUtility::IsHitSpheres(
						playerShip_->GetTransform()->pos,
						GoldShip::COLLISION_RADIUS,
						s->GetPos(),
						s->GetCollisionRadius()
					))
					{
						playerShip_->ChangeState(PlayerState::Destroy);
						mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
					}
				}
			}
		}
	}
	else
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	auto shots = playerShip_->GetPlayerShot();
	for (auto s : shots)
	{
		s->Update();

		if (!(s->IsAlive()))
		{
			continue;
		}

		auto info = MV1CollCheck_Sphere(bossShip_->GetTransform().modelId, -1, s->GetPos(), s->GetCollisionRadius());
		if (info.HitNum >= 1)
		{
			s->CreateExplosion();
		}
		MV1CollResultPolyDimTerminate(info);

		auto turrets = bossShip_->GetTurrets();
		for (auto t : turrets)
		{
			if (!(t->IsAlive()))
			{
				continue;
			}
			if (AsoUtility::IsHitSpheres(
				t->GetPos(),
				Turret::COLLISION_RADIUS,
				s->GetPos(),
				s->GetCollisionRadius()
			))
			{
				t->Damage();
				s->CreateExplosion();
			}
		}
	}

	auto turrets = bossShip_->GetTurrets();
	for (auto t : turrets)
	{
		auto ts = t->GetShot();
		for (auto s : ts)
		{
			s->Update();
			if (!(s->IsAlive()))
			{
				continue;
			}
		}
	}
}

void BattleScene::Draw(void)
{
	spaceDome_->Draw();
	//rockManager_->Draw();
	bossShip_->Draw();
	playerShip_->Draw();
	auto ps = playerShip_->GetPlayerShot();
	for (auto s : ps)
	{
		s->Draw();
	}
	auto turrets = bossShip_->GetTurrets();
	for (auto t : turrets)
	{
		auto ts = t->GetShot();
		for (auto s : ts)
		{
			s->Draw();
		}
	}
}

void BattleScene::Release(void)
{
	spaceDome_->Release();
	delete spaceDome_;

	bossShip_->Release();
	delete bossShip_;

	playerShip_->Release();
	delete playerShip_;

	//rockManager_->Release();
	//delete rockManager_;
}
