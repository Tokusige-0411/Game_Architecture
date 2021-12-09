#include "GoldShip.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SpriteAnimator.h"
#include "ResourceManager.h"
#include "SpeechBalloon.h"
#include "ParticleGenerator.h"

namespace
{
	constexpr float speed = 5.0f;

	constexpr float speedRotX = 1.0f;
	constexpr float speedRotY = 1.0f;
}

GoldShip::GoldShip(SceneManager* manager)
{
	sceneManager_ = manager;
}

GoldShip::~GoldShip()
{
}

void GoldShip::Init(void)
{
	state_ = PlayerState::Normal;
	transform_.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));

	float scale = 10.0f;
	transform_.scl = { scale, scale, scale };
	transform_.pos = AsoUtility::VECTOR_ZERO;
	transform_.quaRot = Quaternion::Euler(0.0f, 0.0f, 0.0f);
	transform_.quaRotLocal = Quaternion();

	transform_.Update();

	sceneManager_->GetCamera()->SetShip(&transform_);

	isDestroy_ = false;

	animator_ = new SpriteAnimator(sceneManager_, ResourceManager::SRC::SHIP_EXPLOSION, 20.0f, 8.0f);

	sBalloon_ = new SpeechBalloon(sceneManager_, SpeechBalloon::TYPE::SPEECH, &transform_);
	sBalloon_->SetText("‚ ‚°‚Ü‚¹‚ñII");
	sBalloon_->SetTime(15.0);
	sBalloon_->SetRelativePos({15.0f, 15.0f, 0.0f});

	particleGenerator_ = new ParticleGenerator(sceneManager_, transform_.pos, 12.0f);
}

void GoldShip::Update(void)
{
	switch (state_)
	{
	case PlayerState::Normal:
		UpdateNormal();
		break;
	case PlayerState::Destroy:
		UpdateDestroy();
		break;
	default:
		break;
	}

	transform_.Update();

	particleGenerator_->Update();
}

void GoldShip::UpdateNormal(void)
{
	ProcessTurn();

	VECTOR forward = transform_.GetForward();
	transform_.pos = VAdd(transform_.pos, VScale(forward, speed));

	particleGenerator_->SetPos(VAdd(transform_.pos, VScale(transform_.GetForward(), 30.0f)));

	auto rot = transform_.quaRot;
	Quaternion axis;
	axis = Quaternion::AngleAxis(AsoUtility::Deg2RadD(180.0), AsoUtility::AXIS_Y);
	rot = rot.Mult(axis);
	axis = Quaternion::AngleAxis(AsoUtility::Deg2RadD(90.0), AsoUtility::AXIS_X);
	rot = rot.Mult(axis);

	particleGenerator_->SetRot(rot);
}

void GoldShip::UpdateDestroy(void)
{
	animator_->Update();

	if (animator_->IsEnd())
	{
		isDestroy_ = true;
	}
}

void GoldShip::Draw(void)
{
	switch (state_)
	{
	case PlayerState::Normal:
		MV1DrawModel(transform_.modelId);
		particleGenerator_->Draw();
		break;
	case PlayerState::Destroy:
		animator_->Draw();
		break;
	default:
		break;
	}

}

void GoldShip::Release(void)
{
	particleGenerator_->Release();
	delete particleGenerator_;
}

void GoldShip::ProcessTurn(void)
{
	if (CheckHitKey(KEY_INPUT_UP)) { Turn(-speedRotX, VECTOR{ 1.0f, 0.0f, 0.0f }); };
	if (CheckHitKey(KEY_INPUT_DOWN)) { Turn(speedRotX, VECTOR{ 1.0f, 0.0f, 0.0f }); };
	if (CheckHitKey(KEY_INPUT_LEFT)) { Turn(-speedRotY, VECTOR{ 0.0f, 1.0f, 0.0f }); };
	if (CheckHitKey(KEY_INPUT_RIGHT)) { Turn(speedRotY, VECTOR{ 0.0f, 1.0f, 0.0f }); };
}

void GoldShip::Turn(float deg, VECTOR axis)
{
	float rad = AsoUtility::Deg2RadF(deg);
	Quaternion tmpQ = Quaternion::AngleAxis(rad, axis);
	transform_.quaRot = transform_.quaRot.Mult(tmpQ);
}

Transform* GoldShip::GetTransform(void)
{
	return &transform_;
}

void GoldShip::ChangeState(PlayerState state)
{
	state_ = state;
	if (state_ == PlayerState::Destroy)
	{
		animator_->Create(transform_.pos);
	}
}

PlayerState GoldShip::GetState(void)
{
	return state_;
}

bool GoldShip::IsDestoy(void)
{
	return isDestroy_;
}

SpeechBalloon* GoldShip::GetSpeechBalloon(void)
{
	return sBalloon_;
}
