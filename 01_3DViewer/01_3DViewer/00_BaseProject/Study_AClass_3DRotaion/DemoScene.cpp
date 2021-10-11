#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "DemoScene.h"
#include "Coin.h"

DemoScene::DemoScene(SceneManager* manager) : SceneBase(manager)
{
	Init();
}

void DemoScene::Init(void)
{
	coin_ = std::make_shared<Coin>(mSceneManager);
}

void DemoScene::Update(void)
{
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

	coin_->Update();
}

void DemoScene::Draw(void)
{
	coin_->Draw();
}

void DemoScene::Release(void)
{
}
