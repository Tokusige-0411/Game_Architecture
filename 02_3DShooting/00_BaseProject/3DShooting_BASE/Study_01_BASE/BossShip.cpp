#include "BossShip.h"
#include "SceneManager.h"
#include "Camera.h"
#include "AsoUtility.h"
#include "EventShot.h"
#include "Turret.h"
#include "GoldShip.h"

BossShip::BossShip(SceneManager* manager, GoldShip* player)
{
	sceneManager_ = manager;
	playerShip_ = player;
}

void BossShip::Init(void)
{
	transform_.modelId = MV1LoadModel("Model/BossShip/BossShip.mv1");
	transform_.scl = { 2.0f, 2.0f, 2.0f };
	transform_.pos = { 0.0f, 0.0f, 4000.0f };
	transform_.quaRot = Quaternion::Euler(
		AsoUtility::Deg2RadF(20.0f),
		AsoUtility::Deg2RadF(210.0f), 
		AsoUtility::Deg2RadF(20.0f)
	);
	transform_.quaRot = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	transform_.Update();

	// ‘O•û
	MakeTurret(
		{ 4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(-18.0f) });
	MakeTurret(
		{ -4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(18.0f) });

	// ‰¡
	MakeTurret(
		{ 4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(90.0f), 0.0f });
	MakeTurret(
		{ -4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(-90.0f), 0.0f });

	// Œã•û
	MakeTurret(
		{ 3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(18.0f) });
	MakeTurret(
		{ -3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(-18.0f) });

	stepEvent_ = 0.0f;

	auto sceneState = sceneManager_->GetmSceneID();
	switch (sceneState)
	{
	case SceneManager::SCENE_ID::EVENT:
		ChangeState(BossState::Event);
		break;
	case SceneManager::SCENE_ID::BATTLE:
		int ret = MV1SetupCollInfo(transform_.modelId, -1, 1, 1, 1);

		ChangeState(BossState::Battle);
		break;
	}
}

void BossShip::Update(void)
{
	switch (state_)
	{
	case BossState::Event:
	{
		VECTOR dir = transform_.GetForward();
		transform_.pos = VAdd(transform_.pos, VScale(dir, speed_move));

		eventShot_->Update();
		if (!eventShot_->IsAlive())
		{
			stepEvent_ -= sceneManager_->GetDeltaTime();
			if (stepEvent_ < 0.0f)
			{
				sceneManager_->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
				return;
			}
		}
		UpdateTurret();
	}
		break;
	case BossState::Battle:
	{
		VECTOR dir = transform_.GetForward();
		transform_.pos = VAdd(transform_.pos, VScale(dir, speed_move));

		float speed = 0.05f * sceneManager_->GetDeltaTime();
		Quaternion axis = Quaternion::AngleAxis(speed, AsoUtility::AXIS_Y);
		transform_.quaRot = transform_.quaRot.Mult(axis);

		MV1RefreshCollInfo(transform_.modelId);

		UpdateTurret();

		//int alived = 0;
		//for (auto t : turrets_)
		//{
		//	if (t->IsAlive())
		//	{
		//		alived++;
		//	}
		//}
		//if (alived == 0)
		//{
		//	ChangeState(BossState::Destroy);
		//}

	}
		break;
	case BossState::Destroy:
		break;
	case BossState::End:
		break;
	default:
		break;
	}
	transform_.Update();
}

void BossShip::UpdateTurret(void)
{
	for (auto& t : turrets_)
	{
		t->Update();
	}
}

void BossShip::Draw(void)
{
	switch (state_)
	{
	case BossState::Event:
		MV1DrawModel(transform_.modelId);
		eventShot_->Draw();
		DrawTurret();
		break;
	case BossState::Battle:
		MV1DrawModel(transform_.modelId);
		DrawTurret();
		break;
	case BossState::Destroy:
		break;
	case BossState::End:
		break;
	default:
		break;
	}
}

void BossShip::DrawTurret(void)
{
	for (auto& t : turrets_)
	{
		t->Draw();
	}
}

void BossShip::Release(void)
{
	MV1DeleteModel(transform_.modelId);

	if (eventShot_ != nullptr)
	{
		eventShot_->Release();
		delete eventShot_;
	}

	for (auto& t : turrets_)
	{
		t->Release();
		delete t;
	}
	turrets_.clear();
}

Transform BossShip::GetTransform(void)
{
	return transform_;
}

std::vector<Turret*> BossShip::GetTurrets(void)
{
	return turrets_;
}

void BossShip::ChangeState(BossState state)
{
	state_ = state;

	switch (state_)
	{
	case BossState::Event:
		stepEvent_ = event_time;
		eventShot_ = new EventShot(sceneManager_, &transform_);
		VECTOR dir = VNorm(VSub(sceneManager_->GetCamera()->GetPos(), transform_.pos));
		eventShot_->Create(transform_.pos, dir);
		break;
	case BossState::Battle:
		break;
	case BossState::Destroy:
		break;
	case BossState::End:
		break;
	default:
		break;
	}
}

void BossShip::MakeTurret(VECTOR localPos, VECTOR localAddAxis)
{
	Turret* t = new Turret(sceneManager_, playerShip_->GetTransform(), &transform_, localPos, localAddAxis);
	t->Init();
	turrets_.emplace_back(t);
}
