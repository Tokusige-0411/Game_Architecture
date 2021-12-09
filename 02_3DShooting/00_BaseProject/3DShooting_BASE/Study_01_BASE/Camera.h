#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"
class SceneManager;
class Transform;

class Camera
{

public:

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };

	enum class MODE
	{
		NONE, 
		FREE, 
		FIXED,
		FOLLOW,
		FOLLOW_SPRING,
		SHAKE,
		MAX
	};

	// �J�����ʒu�ƒ����_�Ƃ̑��΍��W
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -100.0f, 500.0f };

	// ��ڲ԰����̃J�����̈ʒu
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0f, 25.0f, -80.0f };

	// ��ڲ԰����̃J�����̈ʒu
	static constexpr VECTOR RELATIVE_CAMERA_SPRING = { 0.0f, 25.0f, 0.0f };
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFixed(void);
	void SetBeforeDrawFollow(void);
	void SetBeforeDrawFollowSpring(void);
	void SetBeforeDrawShake(void);

	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

	// �J�������[�h�ύX
	void ChangeMode(MODE mode);

	// ���@�̐ݒ�
	void SetShip(Transform* ship);

private:

	SceneManager* mSceneManager;
	Transform* shipTransform_;

	// �J�������[�h
	MODE mMode;

	// �J�����̈ʒu
	VECTOR mPos;

	// �J�����p�x
	Quaternion mQuaRot;

	// �����_
	VECTOR mTargetPos;

	// �J�����̏����
	VECTOR mCameraUp;

	VECTOR mVelocity;

	float stepShake_;
	VECTOR shakeDir_;
	VECTOR defaultPos;
};

