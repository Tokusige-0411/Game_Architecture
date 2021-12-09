#include <cmath>
#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "SpaceDome.h"
#include "Stage.h"
#include "GoldShip.h"
#include "SpeechBalloon.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage(mSceneManager);
	stage_->Init();

	playerShip_ = new GoldShip(mSceneManager);
	playerShip_->Init();

	spaceDome_ = new SpaceDome(mSceneManager, playerShip_->GetTransform());
	spaceDome_->Init();

	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FOLLOW_SPRING);
}

void GameScene::Update(void)
{
	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}

	playerShip_->Update();

	if (!playerShip_->IsDestoy())
	{
		if (playerShip_->GetState() != PlayerState::Destroy)
		{
			auto info = MV1CollCheck_Sphere(stage_->GetModelID(), -1, playerShip_->GetTransform()->pos, GoldShip::COLLISION_RADIUS);
			if (info.HitNum)
			{
				playerShip_->ChangeState(PlayerState::Destroy);
				mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
			}
			MV1CollResultPolyDimTerminate(info);
		}
	}
	else
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}

	auto pPos = playerShip_->GetTransform()->pos;
	auto diffv = VSub(stage_->GetBossPos(), pPos);
	auto diff = diffv.x * diffv.x + diffv.y * diffv.y + diffv.z * diffv.z;
	if (stage_->RADIUS * stage_->RADIUS >= diff)
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}

	spaceDome_->Update();
	stage_->Update();
}

void GameScene::Draw(void)
{
	spaceDome_->Draw();
	stage_->Draw();
	playerShip_->Draw();
	playerShip_->GetSpeechBalloon()->Draw();
}

void GameScene::Release(void)
{
	spaceDome_->Release();
	stage_->Release();
	playerShip_->Release();
}
