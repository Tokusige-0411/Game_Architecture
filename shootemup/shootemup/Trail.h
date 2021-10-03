#pragma once
#include <list>
#include "Geometry.h"

struct HomingShot;
class ParticleSystem;

class Trail
{
	friend ParticleSystem;

public:
	Trail(HomingShot& owner);
	void Update(void);
	void Draw(void);
	void Reset(void);

private:
	HomingShot& owner_;
	std::list<Position2> history_;
	int handle_;
};

