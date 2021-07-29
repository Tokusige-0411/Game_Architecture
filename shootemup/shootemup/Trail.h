#pragma once
#include <list>
#include "HomingShot.h"

class Trail
{
public:
	Trail(HomingShot& owner);
	void Update(void);
	void Draw(void);

private:
	HomingShot& owner_;
	std::list<Position2> history_;
};

