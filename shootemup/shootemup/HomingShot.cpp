#include <DxLib.h>
#include "HomingShot.h"
#include "ParticleSystem.h"

namespace
{
	bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB) {
		Vector2 vec = { posA.x - posB.x, posA.y - posB.y };
		return (radiusA + radiusB) > vec.Magnitude();
	}
}

HomingShot::HomingShot(ParticleSystem& ps, const Position2& pos, const Vector2& vel) : ps_(ps), pos_(pos), vel_(vel)
{
	isActive_ = true;
	trail_ = std::make_unique<Trail>(*this);
	count_ = 0;
	speed_ = 5.0f;
}

HomingShot::~HomingShot()
{
}

const Position2& HomingShot::GetPosition(void)
{
	return pos_;
}

void HomingShot::Draw(const Position2& enPos)
{
	if (!isActive_)
	{
		return;
	}

	if (count_ % 3 == 0)
	{
		vel_ = (vel_ + (enPos - pos_).Normalized()).Normalized() * speed_;
	}

	pos_ += vel_;
	count_++;

	trail_->Draw();

	//’e‚ðŽE‚·
	if (pos_.x + 16 < 0 || pos_.x - 16 > 640 ||
		pos_.y + 24 < 0 || pos_.y - 24 > 480) 
	{
		isActive_ = false;
	}
	if (IsHit(enPos, 5, pos_, 32))
	{
		isActive_ = false;
	}

	DrawCircleAA(pos_.x, pos_.y, 10.0f, 32, 0xff0000);
}
