#include <DxLib.h>
#include "Stage.h"

Stage::Stage(SceneManager* manager)
{
	sceneManager_ = manager;
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
	modelID_ = MV1LoadModel("Model/Rock/Dungeon.mv1");
	MV1SetScale(modelID_, { 1.0f, 1.0f, 1.0f });
	MV1SetPosition(modelID_, { 1000.0f, 400.0f, 1300.0f });
	MV1SetRotationXYZ(modelID_, { 0.0f, 180.0f, 0.0f });

	bossModelID_ = MV1LoadModel("Model/BossShip/BossShip.mv1");
	bossPos_ = { 14500.0f, -800.0f, 6500.0f };
	MV1SetScale(bossModelID_, { 2.0f, 2.0f, 2.0f });
	MV1SetPosition(bossModelID_, bossPos_);
	MV1SetRotationXYZ(bossModelID_, { 0.0f, 180.0f, 0.0f });
}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{
	MV1DrawModel(modelID_);
	MV1DrawModel(bossModelID_);
	DrawGrid();
}

void Stage::DrawGrid(void)
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
}

void Stage::Release(void)
{
	MV1DeleteModel(modelID_);
	MV1DeleteModel(bossModelID_);
}

int Stage::GetModelID(void)
{
	return modelID_;
}

VECTOR Stage::GetBossPos(void)
{
	return bossPos_;
}
