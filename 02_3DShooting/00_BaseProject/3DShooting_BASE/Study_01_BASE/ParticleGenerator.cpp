#include <DxLib.h>
#include <algorithm>
#include "ParticleGenerator.h"
#include "AsoUtility.h"
#include "Particle.h"
#include "SceneManager.h"
#include "Camera.h"

namespace
{
	constexpr int particle_num = 30;

	constexpr float poligon_vertex_num = 10.0f;
	constexpr float split_angle = 360.0f / poligon_vertex_num;

	constexpr float gen_min_size = 3.0f;
	constexpr float gen_max_size = 5.0f;

	constexpr float gen_min_speed = 1.0f;
	constexpr float gen_max_speed = 2.0f;

	constexpr float gen_min_life_time = 1.0f;
	constexpr float gen_max_life_time = 2.0f;

	constexpr float gen_sec = 0.05f;
}

ParticleGenerator::ParticleGenerator(SceneManager* manager, VECTOR pos, float radius)
{
	sceneManager_ = manager;
	pos_ = pos;
	radius_ = radius;
	lightH_ = LoadGraph("Image/Light.png");
}

void ParticleGenerator::Init(void)
{
	CreateSquareVertex();
	CreateCircleVertex();

	for (int i = 0; i < particle_num; i++)
	{
		particle_.emplace_back(new Particle(sceneManager_, lightH_));
	}
	stepGenetare_ = gen_sec;
}

void ParticleGenerator::Update(void)
{
	bool isGenerate = false;
	stepGenetare_ -= sceneManager_->GetDeltaTime();
	if (stepGenetare_ < 0.0f)
	{
		isGenerate = true;
	}

	for (auto& p : particle_)
	{
		p->Update();

		if (!p->isAlive())
		{
			if (isGenerate)
			{
				p = Generate(p);
				stepGenetare_ = gen_sec;
				isGenerate = false;
			}
		}
	}
}

void ParticleGenerator::Draw(void)
{
	auto camera = sceneManager_->GetCamera();
	auto c2t = camera->GetDir();

	VECTOR c2p;
	for (auto& p : particle_)
	{
		c2p = VSub(p->GetPos(), camera->GetPos());

		p->SetZLen(VDot(c2t, c2p));
	}

	std::sort(particle_.begin(), particle_.end(),
		[](Particle* x, Particle* y) {
			return x->GetZLen() > y->GetZLen();
		}
	);

	//DrawBillboard3D(pos_, 0.5f, 0.5f, 100.0f, 0.0f, lightH_, true);
	//DrawMeshSquare();
	//DrawMeshCIrcle();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	for (auto& p : particle_)
	{
		p->Draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ParticleGenerator::DrawMeshSquare(void)
{
	DrawPolygon3D(square_.data(), 2, DX_NONE_GRAPH, true);
}

void ParticleGenerator::DrawMeshCIrcle(void)
{
	DrawPolygonIndexed3D(circle_.data(), circle_.size(), circleIndex_.data(), poligon_vertex_num, DX_NONE_GRAPH, true);
}

void ParticleGenerator::Release(void)
{
	DeleteGraph(lightH_);

	for (auto& p : particle_)
	{
		p->Release();
		delete p;
	}
}

void ParticleGenerator::SetPos(VECTOR pos)
{
	pos_ = pos;
}

void ParticleGenerator::SetRot(Quaternion rot)
{
	quaRot_ = rot;
}

Particle* ParticleGenerator::Generate(Particle* particle)
{
	if (particle == nullptr)
	{
		particle = new Particle(sceneManager_, lightH_);
	}

	VECTOR pos = {0, 0, 0};
	Quaternion rotY = Quaternion::AngleAxis(AsoUtility::Deg2RadF(GetRand(360.0f)), AsoUtility::AXIS_Y);
	
	rotY = quaRot_.Mult(rotY);

	float min = radius_ * (3.0f / 4.0f);


	pos = VAdd(rotY.PosAxis(rotY, { 0.0f, 0.0f, min + static_cast<float>(GetRand(radius_ - min)) }), pos_);


	VECTOR dir = {0, 0, 0};

	float deg = 30 + GetRand(40 - 30);
	deg *= -1.0f;

	Quaternion rotX = Quaternion::AngleAxis(AsoUtility::Deg2RadF(deg), AsoUtility::AXIS_X);
	rotX = rotY.Mult(rotX);
	dir = rotX.GetForward();

	float size = gen_min_size + GetRand(gen_max_size - gen_min_size);
	float speed = gen_min_speed + GetRand(gen_max_speed - gen_min_speed);
	float lifeTime = gen_min_life_time + GetRand(gen_max_life_time - gen_min_life_time);

	particle->Generate(pos, size, dir, speed, lifeTime);

	return particle;
}

void ParticleGenerator::CreateSquareVertex(void)
{
	COLOR_U8 c = GetColorU8(255, 255, 255, 255);

	for (auto& vertex : square_)
	{
		vertex.dif = c;
	}

	float h = 100.0f;
	square_[0].pos = { 0.0f, 0.0f, 0.0f };
	square_[1].pos = { 0.0f, 0.0f, 100.0f };
	square_[2].pos = { 100.0f, 0.0f, 0.0f };
	square_[3].pos = { 100.0f, 0.0f, 0.0f };
	square_[4].pos = { 0.0f, 0.0f, 100.0f };
	square_[5].pos = { 100.0f, 0.0f, 100.0f };


}

void ParticleGenerator::CreateCircleVertex(void)
{
	COLOR_U8 c = GetColorU8(255, 255, 255, 255);

	for (auto& vertex : circle_)
	{
		vertex.dif = c;
	}

	circle_[0].pos = pos_;
	circle_[0].dif = GetColorU8(0, 0, 0, 255);
	float rad = 0.0f;

	for (int i = 1; i < circle_.size(); i++)
	{
		Quaternion tmp = Quaternion::AngleAxis(rad, AsoUtility::AXIS_Y);
		circle_[i].pos = VAdd(tmp.PosAxis(tmp, {0.0f, 0.0f, radius_}), circle_[0].pos);
		rad += AsoUtility::Deg2RadF(split_angle);

		circleIndex_[(i - 1) * 3] = 0;
		circleIndex_[(i - 1) * 3 + 1] = (i - 1) + 1;
		circleIndex_[(i - 1) * 3 + 2] = (i - 1) + 2;
	}
	circleIndex_[circleIndex_.size() - 1] = 1;
}
