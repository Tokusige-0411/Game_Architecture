#include "RovckManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "AsoUtility.h"
#include "Rock.h"

RockManager::RockManager()
{
}

RockManager::~RockManager()
{
}

void RockManager::Init(SceneManager* sManager, Transform* pTransform)
{
	sceneManager_ = sManager;
	playerTransform_ = pTransform;
	resourceManager_ = sceneManager_->GetResource();
}

void RockManager::Update(void)
{
	VECTOR mapPos = playerTransform_->pos;

	IntVector3 cMapPos = { 0, 0, 0 };
	if (!rockMap_.count(cMapPos))
	{
		std::vector<Rock*> rocks;

		rocks.push_back(CreateRandom(cMapPos));

		rockMap_.emplace(cMapPos, rocks);
	}
}

void RockManager::Draw(void)
{
	for (auto& p : rockMap_)
	{
		for (auto& rock : p.second)
		{
			rock->Draw();
		}
	}
}

void RockManager::Release(void)
{
	for (auto& p : rockMap_)
	{
		for (auto& rock : p.second)
		{
			rock->Draw();
		}
	}
	rockMap_.clear();
}

Rock* RockManager::CreateRandom(IntVector3 map)
{
	int r = GetRand(1);
	int id = -1;

	if (r)
	{
		id = resourceManager_->LoadModelDuplicate(ResourceManager::SRC::ROCK02);
	}
	else
	{
		id = resourceManager_->LoadModelDuplicate(ResourceManager::SRC::ROCK01);
	}

	VECTOR angle = { AsoUtility::Deg2RadF(GetRand(360)), AsoUtility::Deg2RadF(GetRand(360)), 0.0f };

	int s = 2 + GetRand(8);
	VECTOR scale = { s, s, s };

		
	Rock* ro = new Rock();

	return nullptr;
}
