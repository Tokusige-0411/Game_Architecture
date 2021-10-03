#include <DxLib.h>
#include "Stage.h"

Stage::Stage(SceneManager* manager)
{
	mSceneManager = manager;
	modelID_ = MV1LoadModel("Model/Stage.mv1");
	pos_ = { 0.0f, -100.0f, 0.0f };
	MV1SetPosition(modelID_, pos_);
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	float line = -500.0f;
	for (int i = 0; i < 11; i++)
	{
		// XŽ²
		DrawLine3D({ -500.0f, 0.0f, line }, { 500.0f, 0.0f, line }, 0xff0000);

		// ZŽ²
		DrawLine3D({ line, 0.0f, -500.0f }, { line, 0.0f, 500.0f }, 0x0000ff);

		line += 100.0f;
	}
	MV1DrawModel(modelID_);
}

void Stage::Release(void)
{
	MV1DeleteModel(modelID_);
}
