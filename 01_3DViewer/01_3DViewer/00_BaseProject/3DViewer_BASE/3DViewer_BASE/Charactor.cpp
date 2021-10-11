#include "Charactor.h"
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"

namespace
{
	constexpr float rotSpeed = 5.0f * (DX_PI_F / 180.0f);
}

Charactor::Charactor(SceneManager* manager)
{
	mSceneManager = manager;
	Init();
}

Charactor::~Charactor()
{
}

void Charactor::Init(void)
{
	modelID_ = MV1LoadModel("Model/Human.mv1");

	animTime_ = 0.0f;
	animID_ = MV1AttachAnim(modelID_, 1, -1, false);
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelID_, animID_);

	pos_ = { 0.0f, 0.0f, 0.0f };
	angles_ = { 0.0f, 0.0f, 0.0f };
	localAngles_ = { 0.0, AsoUtility::Deg2RadF(180.0f), 0.0f };
	speed_ = 5.0f;

	MV1SetPosition(modelID_, pos_);
}

void Charactor::Update(void)
{
	auto move = [&](int key, float rotRad) {
		if (CheckHitKey(key))
		{
			auto& camera = mSceneManager->GetCamera()->GetAngles();
			rotRad += camera.y;

			// ƒJƒƒ‰‚ÌŒü‚«‚É‰ñ“]
			auto diff = AsoUtility::RadIn2PI(rotRad) - AsoUtility::RadIn2PI(angles_.y);
			if (fabsf(diff) > AsoUtility::Deg2RadF(5.0f))
			{
				float a = AsoUtility::DirNearAroundRad(angles_.y, rotRad);
				angles_.y += rotSpeed * (float)a;
			}
			else
			{

			}

			// ƒJƒƒ‰‚ÌŒü‚«‚ÉˆÚ“®
			rotRad -= AsoUtility::Deg2RadF(90.0f);
			pos_.x += cosf(rotRad) * speed_;
			pos_.z -= sinf(rotRad) * speed_;
		}
	};

	move(KEY_INPUT_W, 0.0f);
	move(KEY_INPUT_S, AsoUtility::Deg2RadF(180.0f));
	move(KEY_INPUT_A, AsoUtility::Deg2RadF(-90.0f));
	move(KEY_INPUT_D, AsoUtility::Deg2RadF(90.0f));

	MV1SetRotationXYZ(modelID_, { angles_.x + localAngles_.x, angles_.y + localAngles_.y , angles_.z + localAngles_.z });
	MV1SetPosition(modelID_, pos_);

	animTime_ += mSceneManager->GetDeltaTime() * 20.0f;
	if (animTime_ >= totalAnimTime_)
	{
		animTime_ = 0.0f;
	}
	MV1SetAttachAnimTime(modelID_, animID_, animTime_);
}

void Charactor::Draw(void)
{
	MV1DrawModel(modelID_);
}

const VECTOR& Charactor::GetPos(void)
{
	return pos_;
}

const VECTOR& Charactor::GetAngles(void)
{
	return angles_;
}
