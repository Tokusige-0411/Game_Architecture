#pragma once
#include <memory>
#include "Trail.h"
#include "Geometry.h"

class ParticleSystem;

class HomingShot
{
	friend ParticleSystem;

public:
	HomingShot(ParticleSystem& ps, const Position2& pos, const Vector2& vel);
	~HomingShot();

	const Position2& GetPosition(void);

	void Draw(const Position2& enPos);

private:
	Position2 pos_;				//���W
	Vector2 vel_;				//���x
	bool isActive_;				//�����Ă邩�`�H
	int count_;
	float speed_;
	std::unique_ptr<Trail> trail_;
	ParticleSystem& ps_;
};
