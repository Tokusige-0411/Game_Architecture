#include <DxLib.h>
#include "Particle.h"
#include "SceneManager.h"

Particle::Particle(SceneManager* manager, int image)
{
	sceneManager_ = manager;
	imageH_ = image;
}

void Particle::Generate(VECTOR pos, float size, VECTOR dir, float speed, float lifeTime)
{
	pos_ = pos;
	dir_ = dir;
	size_ = size;
	speed_ = speed;
	lifeTime_ = lifeTime;
}

void Particle::Init(void)
{
}

void Particle::Update(void)
{
	pos_ = VAdd(pos_, VScale(dir_, speed_));
}

void Particle::Draw(void)
{
	DrawBillboard3D(pos_, 0.5f, 0.5f, size_, 0.0f, imageH_, true);
}

void Particle::Release(void)
{
}
