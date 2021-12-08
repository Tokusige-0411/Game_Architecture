#include "Rock.h"

Rock::Rock()
{
}

Rock::~Rock()
{
}

void Rock::Init(int modelID, VECTOR pos, VECTOR angle, VECTOR scale)
{
	// ÉÇÉfÉãÇÃäÓñ{èÓïÒ
	transform_.SetModel(modelID);
	transform_.scl = scale;
	transform_.pos = pos;
	transform_.quaRot = Quaternion::Euler(angle);
	transform_.quaRotLocal = Quaternion();
	transform_.Update();
}

void Rock::Update(void)
{
}

void Rock::Draw(void)
{
	MV1DrawModel(transform_.modelId);
}

void Rock::DrawGrid(void)
{
}

void Rock::Release(void)
{
}
