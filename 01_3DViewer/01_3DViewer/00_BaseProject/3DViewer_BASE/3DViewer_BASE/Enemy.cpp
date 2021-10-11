#include <DxLib.h>
#include "Enemy.h"
#include "Charactor.h"
#include "AsoUtility.h"

namespace
{
	constexpr float viewRange = 300.0f;
	constexpr float viewAngle = 30.0f * (DX_PI_F / 180.0f);
}

Enemy::Enemy(SceneManager* manager, Charactor* chara)
{
	mSceneManager = manager;
	chara_ = chara;
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Init(void)
{
	modelID_ = MV1LoadModel("Model/Human.mv1");
	pos_ = { 0.0f, 0.0f, 500.0f };

	angles_ = { 0.0f, AsoUtility::Deg2RadF(45.0f), 0.0f };
	localAngles_ = { 0.0, AsoUtility::Deg2RadF(180.0f), 0.0f };

	MV1SetPosition(modelID_, pos_);
}

void Enemy::Update(void)
{
	MV1SetMaterialDifColor(modelID_, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	VECTOR length = VNorm(VSub(chara_->GetPos(), pos_));
	float lengthSize = VSize(length);
	if (viewRange >= lengthSize)
	{
		VECTOR lineEnd = VAdd(pos_, { viewRange * sinf(angles_.y), 0.0f, viewRange * cosf(angles_.y) });
		VECTOR vec = VNorm(VSub(lineEnd, pos_));
		if (VDot(vec, length) > cosf(viewAngle))
		{
			MV1SetMaterialDifColor(modelID_, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	MV1SetRotationXYZ(modelID_, { angles_.x + localAngles_.x, angles_.y + localAngles_.y , angles_.z + localAngles_.z });
}

void Enemy::Draw(void)
{
	MV1DrawModel(modelID_);

	VECTOR lineEnd = VAdd(pos_, {viewRange * sinf(angles_.y), 0.0f, viewRange * cosf(angles_.y) });
	VECTOR lineEnd1 = VAdd(pos_, { viewRange * sinf(angles_.y + viewAngle), 0.0f, viewRange * cosf(angles_.y + viewAngle) });
	VECTOR lineEnd2= VAdd(pos_, { viewRange * sinf(angles_.y - viewAngle), 0.0f, viewRange * cosf(angles_.y - viewAngle) });
	DrawTriangle3D(pos_, lineEnd2, lineEnd, 0xffffff, true);
	DrawTriangle3D(pos_, lineEnd, lineEnd1, 0xffffff, true);
}
