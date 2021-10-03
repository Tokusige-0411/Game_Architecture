#include <DxLib.h>
#include "Trail.h"
#include "HomingShot.h"

namespace
{
	constexpr size_t history_limit = 30;
}

Trail::Trail(HomingShot& owner):owner_(owner)
{
	handle_ = LoadGraph("img/arrow2.png");
}

void Trail::Update(void)
{
	history_.push_front(owner_.GetPosition());
	if (history_.size() >= history_limit)
	{
		history_.pop_back();
	}
}

void Trail::Draw(void)
{
	history_.push_front(owner_.GetPosition());
	if (history_.size() >= history_limit)
	{
		history_.pop_back();
	}
	//Position2 lastPos = owner_.GetPosition();
	//float thickness = 20.0f;
	//float div = 1.0f / static_cast<float>(history_limit);
	//float u = 0.0f;

	//for (const auto& pos : history_)
	//{
	//	if (lastPos == pos)continue;
	//	DrawLineAA(lastPos.x, lastPos.y, pos.x, pos.y, 0xffffff, thickness);
	//	thickness *= 0.7f;

	//	auto v = pos - lastPos;
	//	v.Normalize();
	//	v = Vector2(-v.y, v.x);
	//	auto p1 = lastPos + v * 16.0f;
	//	auto p2 = pos + v * 16.0f;
	//	auto p3 = pos - v * 16.0f;
	//	auto p4 = lastPos - v * 16.0f;

	//	DrawRectModiGraphF(
	//		p1.x, p1.y,
	//		p2.x, p2.y,
	//		p3.x, p3.y,
	//		p4.x, p4.y,
	//		u * 256, 0,
	//		div * 256, 64,
	//		handle_, true
	//	);

	//	u += div;
	//	lastPos = pos;
	//}
}

void Trail::Reset(void)
{
	history_.clear();
}
