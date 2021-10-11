#include <math.h>
#include "DxLib.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Camera.h"

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
	Init();
}

Camera::~Camera()
{
}

void Camera::Init()
{
	pos_ = {0.0f, 50.0f, -100.0f};
	targetPos_ = { 0.0f, 50.0f, 100.0f };
	up_ = { 0.0f, 1.0f, 0.0f };
}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{
	SetCameraPositionAndTargetAndUpVec(pos_, targetPos_, up_);
}

void Camera::Draw()
{
}

void Camera::Release(void)
{
}
