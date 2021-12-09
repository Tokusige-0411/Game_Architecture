#include "EventScene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "BossShip.h"
#include "SpaceDome.h"
#include "KeyCheck.h"

EventScene::EventScene(SceneManager* manager):SceneBase(manager)
{
}

void EventScene::Init(void)
{
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED);

	bossShip_ = new BossShip(mSceneManager, nullptr);
	bossShip_->Init();

	spaceDome_ = new SpaceDome(mSceneManager, nullptr);
	spaceDome_->Init();
}

void EventScene::Update(void)
{
	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}

	spaceDome_->Update();
	bossShip_->Update();

}

void EventScene::Draw(void)
{
	spaceDome_->Draw();
	bossShip_->Draw();
}

void EventScene::Release(void)
{
	spaceDome_->Release();
	delete spaceDome_;

	bossShip_->Release();
	delete bossShip_;
}
