#include <DxLib.h>
#include "ParticleGenerator.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Particle.h"

namespace
{
	constexpr float poligon_vertex_num = 10.0f;
	constexpr float split_angle = 360.0f / poligon_vertex_num;
}

ParticleGenerator::ParticleGenerator(SceneManager* manager, VECTOR pos, float radius)
{
	sceneManager_ = manager;
	pos_ = pos;
	radius_ = radius;
	lightH_ = LoadGraph("Image/Light.png");

	for (auto& p : particle_)
	{
		p = Generate(p);
	}
}

void ParticleGenerator::Init(void)
{
	CreateSquareVertex();
	CreateCircleVertex();
}

void ParticleGenerator::Update(void)
{
	for (auto& p : particle_)
	{
		p->Update();
	}
}

void ParticleGenerator::Draw(void)
{
	DrawBillboard3D(pos_, 0.5f, 0.5f, 100.0f, 0.0f, lightH_, true);
	for (auto& p : particle_)
	{
		p->Draw();
	}
	DrawMeshSquare();
	DrawMeshCIrcle();
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
}

Particle* ParticleGenerator::Generate(Particle* particle)
{
	if (particle == nullptr)
	{
		particle = new Particle(sceneManager_, lightH_);
	}

	VECTOR pos;
	Quaternion pTmp = Quaternion::AngleAxis(AsoUtility::Deg2RadF(GetRand(360)), AsoUtility::AXIS_Y);
	pos = VAdd(pTmp.PosAxis(pTmp, { 0.0f, 0.0f, static_cast<float>(GetRand(radius_)) }), pos_);

	VECTOR dir;
	float deg = 60 + GetRand(80 - 60);
	deg *= -1.0f;
	Quaternion dTmp = Quaternion::AngleAxis(AsoUtility::Deg2RadF(deg), AsoUtility::AXIS_X);
	dTmp = pTmp.Mult(dTmp);
	dir = dTmp.GetForward();

	float size = GetRand(8) + 2;
	float speed = GetRand(3) + 1;

	particle->Generate(pos, size, dir, speed, 10.0f);

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
