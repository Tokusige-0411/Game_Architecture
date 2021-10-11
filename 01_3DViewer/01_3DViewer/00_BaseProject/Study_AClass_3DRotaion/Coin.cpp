#include "Coin.h"
#include "AsoUtility.h"

namespace 
{
	constexpr float size = 15.0f;
	constexpr VECTOR scale = { size, size, size };
}

Coin::Coin(SceneManager* manager)
{
	Init();
}

void Coin::Init(void)
{
	modelID_ = MV1LoadModel("Model/Coin.mv1");
	pos_ = { 0.0f, 50.0f, 0.0f };
	angles_ = { 0.0f, 0.0f, 0.0f };


	float localRadX = AsoUtility::Deg2RadF(-90.0f);
	float localRadY = AsoUtility::Deg2RadF(0.0f);
	float localRadZ = AsoUtility::Deg2RadF(0.0f);

	//// VECTOR
	//localAngles_ = { AsoUtility::Deg2RadF(-90.0f), 0.0f, 0.0f };
	//MV1SetRotationXYZ(modelID_, VAdd(angles_, localAngles_));

	// MATRIX
	matRotLocal_ = MGetIdent();
	matRotLocal_ = MMult(matRotLocal_, MGetRotX(localRadX));
	matRotLocal_ = MMult(matRotLocal_, MGetRotY(localRadY));
	matRotLocal_ = MMult(matRotLocal_, MGetRotZ(localRadZ));
	MV1SetMatrix(modelID_, matRotLocal_);

	MV1SetPosition(modelID_, pos_);
	MV1SetScale(modelID_, scale);

	updateType_ = Type::Matrix;
}

void Coin::Update(void)
{
	angles_ = VAdd(angles_, { 0.0f, AsoUtility::Deg2RadF(1.0f), 0.0f });

	switch (updateType_)
	{
	case(Type::Vector):
		SetModelVector();
		break;
	case(Type::Matrix):
		SetModelMatrix();
		break;
	default:
		break;
	}
}

void Coin::Draw(void)
{
	DrawDirection();
	MV1DrawModel(modelID_);
}

void Coin::SetModelVector(void)
{
	MV1SetRotationXYZ(modelID_, VAdd(angles_, localAngles_));
}

void Coin::SetModelMatrix(void)
{
	matScl_ = MGetScale(scale);

	matRot_ = MGetIdent();

	matRot_ = MMult(matRot_, matRotLocal_);
	matRot_ = MMult(matRot_, MGetRotX(angles_.x));
	matRot_ = MMult(matRot_, MGetRotY(angles_.y));
	matRot_ = MMult(matRot_, MGetRotZ(angles_.z));

	matTrn_ = MGetTranslate(pos_);

	MATRIX mat = MGetIdent();

	mat = MMult(mat, matScl_);
	mat = MMult(mat, matRot_);
	mat = MMult(mat, matTrn_);

	MV1SetMatrix(modelID_, mat);
}

void Coin::DrawDirection(void)
{
	MATRIX mat = MGetIdent();

	switch (updateType_)
	{
	case(Type::Vector):
		break;
	case(Type::Matrix):
		mat = matRot_;
		break;
	default:
		break;
	}

	
	VECTOR forward = VNorm(VTransform({ 0.0f, 0.0f, 1.0f }, mat));
	VECTOR right = VNorm(VTransform({ 1.0f, 0.0f, 0.0f }, mat));
	VECTOR up = VNorm(VTransform({ 0.0f, 1.0f, 0.0f }, mat));

	VECTOR dir;
	VECTOR s;
	VECTOR e;
	float len = 30.0f;
	float size = 3.0f;

	dir = forward;
	s = VAdd(pos_, VScale(dir, -len));
	e = VAdd(pos_, VScale(dir, +len));
	DrawLine3D(s, e, 0x0000ff);
	DrawSphere3D(e, size, 10, 0x0000ff, 0x0000ff, true);

	dir = right;
	s = VAdd(pos_, VScale(dir, -len));
	e = VAdd(pos_, VScale(dir, +len));
	DrawLine3D(s, e, 0xff0000);
	DrawSphere3D(e, size, 10, 0xff0000, 0xff0000, true);

	dir = up;
	s = VAdd(pos_, VScale(dir, -len));
	e = VAdd(pos_, VScale(dir, +len));
	DrawLine3D(s, e, 0x00ff00);
	DrawSphere3D(e, size, 10, 0x00ff00, 0x00ff00, true);
}
