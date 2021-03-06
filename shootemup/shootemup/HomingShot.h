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
	Position2 pos_;				//座標
	Vector2 vel_;				//速度
	bool isActive_;				//生きてるか〜？
	int count_;
	float speed_;
	std::unique_ptr<Trail> trail_;
	ParticleSystem& ps_;
};
