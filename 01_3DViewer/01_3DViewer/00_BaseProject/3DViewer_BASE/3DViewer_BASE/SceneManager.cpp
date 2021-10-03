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

	mScene = new TitleScene(this);
	mScene->Init();

	mCamera = std::make_shared<Camera>();

	mMiniCamera = new MiniCamera(mCamera.get());
	mMiniCamera->Init();

	mIsSceneChanging = false;

	// �f���^�^�C��
	mTickCount = std::chrono::system_clock::now();

	// 3D�p�������֐�
	Init3D();
}

void SceneManager::Init3D(void)
{
	// Z�o�b�t�@�̏�����
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

	// �f���^�^�C��
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

	// �~�j�J����
	mMiniCamera->Update();
	mMiniCamera->DrawScreen();

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	// �J�����̐ݒ�
	mCamera->SetBeforeDraw();

	// �`��
	mScene->Draw();
	mCamera->Draw();

	// �~�j�J����
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



