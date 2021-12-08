#include "BossShip.h"
#include "SceneManager.h"

BossShip::BossShip(SceneManager* manager, GoldShip* player)
{
	sceneManager_ = manager;
	playerShip_ = player;
}

void BossShip::Init(void)
{
	transform_.modelId = MV1LoadModel("Model/BossShip/BossShip.mv1");
	transform_.scl = { 2.0f, 2.0f, 2.0f };
	transform_.pos = { 0.0f, 0.0f, 4000.0f };




	auto sceneState = sceneManager_->GetmSceneID();
	switch (sceneState)
	{
	case SceneManager::SCENE_ID::NONE:
		break;
	case SceneManager::SCENE_ID::TITLE:
		break;
	case SceneManager::SCENE_ID::GAME:
		break;
	case SceneManager::SCENE_ID::EVENT:
		state_ = BossState::Event;
		break;
	case SceneManager::SCENE_ID::BATTLE:
		state_ = BossState::Battle;
		break;
	default:
		break;
	}
}

void BossShip::Update(void)
{
	transform_.Update();
}

void BossShip::Draw(void)
{
	MV1DrawModel(transform_.modelId);
}

void BossShip::Release(void)
{
}
