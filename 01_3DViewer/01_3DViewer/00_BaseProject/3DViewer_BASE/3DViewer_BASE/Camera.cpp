#include "Camera.h"
#include "AsoUtility.h"

Camera::Camera()
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	pos_ = { 0.0f, 200.0f, -500.0f };
	angles_ = {
		static_cast<float>(AsoUtility::Deg2Rad(30.0)) , 0.0f, 0.0f
	};
	speed_ = 5.0f;
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

	auto tmpAngle = angles_.y - static_cast<float>(AsoUtility::Deg2Rad(90.0));
	if (CheckHitKey(KEY_INPUT_W))
	{
		pos_.x += cosf(tmpAngle) * speed_;
		pos_.z -= sinf(tmpAngle) * speed_;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		pos_.x += cosf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(180.0))) * speed_;
		pos_.z -= sinf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(180.0))) * speed_;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		pos_.x += cosf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
		pos_.z -= sinf(tmpAngle - static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		pos_.x += cosf(tmpAngle + static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
		pos_.z -= sinf(tmpAngle + static_cast<float>(AsoUtility::Deg2Rad(90.0))) * speed_;
	}
}

void Camera::SetBeforeDraw(void)
{
	SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
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
