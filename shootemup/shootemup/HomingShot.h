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
	Position2 pos_;				//ç¿ïW
	Vector2 vel_;				//ë¨ìx
	bool isActive_;				//ê∂Ç´ÇƒÇÈÇ©Å`ÅH
	int count_;
	float speed_;
	std::unique_ptr<Trail> trail_;
	ParticleSystem& ps_;
};
