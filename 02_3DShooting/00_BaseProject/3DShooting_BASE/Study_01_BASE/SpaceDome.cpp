#include "SpaceDome.h"
#include "AsoUtility.h"

SpaceDome::SpaceDome(SceneManager* manager, Transform* playerTrans)
{
	sceneManager_ = manager;
	playerTrans_ = playerTrans;
}

SpaceDome::~SpaceDome()
{
}

void SpaceDome::Init(void)
{
	transform_.SetModel(MV1LoadModel("Model/SkyDome/SkyDome.mv1"));

	float scale = 1.0f;
	transform_.scl = { scale, scale, scale };
	transform_.pos = AsoUtility::VECTOR_ZERO;
	transform_.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	transform_.quaRotLocal = Quaternion();

	state_ = State::Follow;

	MV1SetWriteZBuffer(transform_.modelId, false);

	transform_.Update();
}

void SpaceDome::Update(void)
{
	switch (state_)
	{
	case SpaceDome::State::Stay:
		transform_.pos = AsoUtility::VECTOR_ZERO;
		break;
	case SpaceDome::State::Follow:
		if (playerTrans_ != nullptr)
		{
			transform_.pos = playerTrans_->pos;
		}
		break;
	default:
		break;
	}
	transform_.Update();
}

void SpaceDome::Draw(void)
{
	MV1DrawModel(transform_.modelId);
}

void SpaceDome::Release(void)
{
}

void SpaceDome::ChangeState(State state)
{
	state_ = state;
}
