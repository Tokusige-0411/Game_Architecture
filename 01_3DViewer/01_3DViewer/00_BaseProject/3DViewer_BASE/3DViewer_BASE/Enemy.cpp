#include "Enemy.h"

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
	pos_ = { 0.0f, 0.0f, 0.0f };
}

void Enemy::Update(void)
{
}

void Enemy::Draw(void)
{
}
