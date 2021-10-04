#include "Camera.h"
#include "Charactor.h"
#include "AsoUtility.h"

namespace
{
	constexpr float hieght = 300.0f;
	constexpr float toTargetDis = 500.0f;
}

Camera::Camera()
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	pos_ = { 0.0f, hieght, toTargetDis };
	angles_ = {
		static_cast<float>(AsoUtility::Deg2Rad(30.0)) , 0.0f, 0.0f
	};
	speed_ = 5.0f;
	target_ = { 0.0f, 0.0f, 0.0f };
}

void Camera::Update(void)
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		angles_.y += static_cast<float>(AsoUtility::Deg2Rad(1.0));
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		angles_.y -= static_cast<float>(AsoUtility::Deg2Rad(1.0));
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		angles_.x -= static_cast<float>(AsoUtility::Deg2Rad(1.0));
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		angles_.x += static_cast<float>(AsoUtility::Deg2Rad(1.0));
	}

	//auto tmpAngle = angles_.y - static_cast<float>(AsoUtility::Deg2Rad(90.0));
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	pos_.x += cosf(tmpAngle) * speed_;
	//	pos_.z -= sinf(tmpAngle) * speed_;
	//}
	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	pos_.x += cosf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(180.0))) * speed_;
	//	pos_.z -= sinf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(180.0))) * speed_;
	//}
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	pos_.x += cosf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
	//	pos_.z -= sinf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
	//}
	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	pos_.x += cosf(tmpAngle + static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
	//	pos_.z -= sinf(tmpAngle + static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
	//}


}

void Camera::SetBeforeDraw(void)
{
	if (chara_ != nullptr)
	{
		target_ = chara_->GetPos();

		auto dirX = sinf(angles_.y);
		auto dirZ = cosf(angles_.y);

		auto dir = VNorm({ dirX, 0.0f, dirZ });
		auto offset = VScale(dir, 200);

		target_ = VAdd(target_, offset);

		auto revRad = AsoUtility::Deg2RadF(180.0f);
		auto rdirX = sinf(angles_.y + revRad);
		auto rdirZ = cosf(angles_.y + revRad);

		auto rdir = VNorm({ rdirX, 0.0f, rdirZ });
		auto movePow = VScale(rdir, toTargetDis);

		pos_ = VAdd(target_, movePow);
		pos_.y = hieght;

		SetCameraPositionAndTargetAndUpVec(pos_, target_, { 0.0f, 1.0f, 0.0f });
	}
	else
	{
		//SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
	}
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

const VECTOR& Camera::GetPos(void)const
{
	return pos_;
}

const VECTOR& Camera::GetAngles(void)const
{
	return angles_;
}

void Camera::SetUnit(Charactor* chara)
{
	chara_ = chara;
}

void Camera::SetTarget(const VECTOR& target)
{
	target_ = target;
}
