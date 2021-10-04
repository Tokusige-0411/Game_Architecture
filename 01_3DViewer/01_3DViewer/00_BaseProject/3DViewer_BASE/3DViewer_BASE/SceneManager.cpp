#include <chrono>
#include "DxLib.h"
#include "Fader.h"
#include "TitleScene.h"
#include "Camera.h"
#include "MiniCamera.h"
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Charactor.h"

void SceneManager::Init()
{

	mSceneID = SCENE_ID::TITLE;
	mWaitSceneID = SCENE_ID::NONE;

	mFader = new Fader();
	mFader->Init();

	mCamera = std::make_shared<Camera>();

	mScene = new TitleScene(this);
	mScene->Init();

	mMiniCamera = new MiniCamera(mCamera.get());
	mMiniCamera->Init();

	mIsSceneChanging = false;

	// デルタタイム
	mTickCount = std::chrono::system_clock::now();

	// 3D用初期化関数
	Init3D();
}

void SceneManager::Init3D(void)
{
	// Zバッファの初期化
	SetUseZBuffer3D(true);

	SetWriteZBuffer3D(true);

	SetUseBackCulling(true);

	SetCameraNearFar(0.0f, 1500.0f);

	ChangeLightTypeDir({0.3f, -0.7f, 0.8});


}

void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// デルタタイム
	auto tickCount = std::chrono::system_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - mTickCount).count() / 1000000000.0f;
	mTickCount = tickCount;

	mFader->Update();
	if (mIsSceneChanging)
	{
		Fader::FADE_STATE fState = mFader->GetState();
		switch (fState)
		{
		case Fader::FADE_STATE::FADE_IN:
			if (mFader->IsEnd())
			{
				mFader->SetFade(Fader::FADE_STATE::NONE);
				mIsSceneChanging = false;
			}
			break;
		case Fader::FADE_STATE::FADE_OUT:
			if (mFader->IsEnd())
			{
				DoChangeScene();
				mFader->SetFade(Fader::FADE_STATE::FADE_IN);
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		mScene->Update();
	}

	mCamera->Update();

	// ミニカメラ
	mMiniCamera->Update();
	mMiniCamera->DrawScreen();

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();

	// カメラの設定
	mCamera->SetBeforeDraw();

	// 描画
	mScene->Draw();
	mCamera->Draw();

	// ミニカメラ
	mMiniCamera->Draw();

	mFader->Draw();
}

void SceneManager::Release(void)
{
	mScene->Release();
	delete mScene;
}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{
	mWaitSceneID = nextId;

	if (isFading)
	{
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		mIsSceneChanging = true;
	}
	else 
	{
		DoChangeScene();
	}

}

float SceneManager::GetDeltaTime(void)
{
	return mDeltaTime;
}

Camera* SceneManager::GetCamera(void)
{
	return mCamera.get();
}

void SceneManager::DoChangeScene(void)
{
	mScene->Release();

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		mScene = new TitleScene(this);
		break;
	default:
		break;
	}

	mScene->Init();

	mWaitSceneID = SCENE_ID::NONE;

}



