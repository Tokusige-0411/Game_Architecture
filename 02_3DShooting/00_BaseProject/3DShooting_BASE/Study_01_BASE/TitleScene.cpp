#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TitleScene.h"
#include "SpaceDome.h"
#include "ParticleGenerator.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mImgStartLogo = LoadGraph("Image/StartLogo.png");

	spaceDome_ = new SpaceDome(mSceneManager, nullptr);
	spaceDome_->Init();

	particleGenerator_ = new ParticleGenerator(mSceneManager, { 0.0f, 0.0f, 0.0f }, 20.0f);
	particleGenerator_->Init();

	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FREE);
}

void TitleScene::Update(void)
{

	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}

	particleGenerator_->Update();

}

void TitleScene::Draw(void)
{
	spaceDome_->Draw();
	particleGenerator_->Draw();
	// ƒƒS•`‰æ
	DrawLogo();
}

void TitleScene::DrawLogo(void)
{

	int cx = SCREEN_SIZE_X / 2;
	int cy = SCREEN_SIZE_Y / 2;
	DrawRotaGraph(
		cx, cy - 200,
		1.0f, 0.0f, mImgStartLogo, true);

	char* msg = (char*)"Push Space";
	SetFontSize(28);
	int len = (int)strlen(msg);
	int width = GetDrawStringWidth(msg, len);
	DrawFormatString((SCREEN_SIZE_X / 2) - (width / 2), 200, 0x87cefa, msg);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetFontSize(16);
	
}

void TitleScene::Release(void)
{

	DeleteGraph(mImgStartLogo);
	spaceDome_->Release();
}
