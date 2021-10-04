#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Charactor.h"
#include "Camera.h"
#include "RollBall.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
	mSceneManager = manager;

	stage_ = std::make_unique<Stage>(manager);

	charactor_ = std::make_shared<Charactor>(manager);
	mSceneManager->GetCamera()->SetUnit(charactor_.get());

	ball_ = std::make_shared<RollBall>(manager, charactor_.get());
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
	ball_->Update();
}

void TitleScene::Draw(void)
{
	stage_->Draw();
	charactor_->Draw();
	ball_->Draw();
}

void TitleScene::Release(void)
{
}
