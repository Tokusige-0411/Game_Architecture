#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Charactor.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
	stage_ = std::make_unique<Stage>(manager);
	charactor_ = std::make_shared<Charactor>(manager);
}

void TitleScene::Init(void)
{
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

	stage_->Update();
	charactor_->Update();
}

void TitleScene::Draw(void)
{
	stage_->Draw();
	charactor_->Draw();;
}

void TitleScene::Release(void)
{
}
