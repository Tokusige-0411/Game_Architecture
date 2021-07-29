#pragma once
#include "Trail.h"
#include "Geometry.h"

struct Bullet {
	Position2 pos;//À•W
	Vector2 vel;//‘¬“x
	bool isActive = false;//¶‚«‚Ä‚é‚©`H
};

struct HomingShot : public Bullet
{
	Trail trail;
	HomingShot();
};
