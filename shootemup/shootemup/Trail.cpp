#include "Trail.h"

namespace
{
	constexpr size_t trail_limit = 10;
}

Trail::Trail(HomingShot& owner):owner_(owner)
{
}

void Trail::Update(void)
{
	history_.push_front(owner_.pos);
	if (history_.size() >= trail_limit)
	{
		history_.pop_back();
	}
}

void Trail::Draw(void)
{
	float thickness = 30.0f;
}
