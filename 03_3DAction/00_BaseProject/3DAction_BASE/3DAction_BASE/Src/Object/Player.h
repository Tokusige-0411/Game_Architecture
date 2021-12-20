#pragma once
#include <DxLib.h>
#include "Common/Transform.h"
class SceneManager;
class ResourceManager;
class GravityManager;
class AnimationController;
class Capsule;
class Collider;

class Player
{

public:

	static constexpr float SPEED_MOVE = 5.0f;

	static constexpr float SPEED_RUN = 10.0f;

	static constexpr float TIME_ROT = 1.0f;

	static constexpr float JUMP_POW = 35.0f;

	static constexpr float JUMP_TIME_IN = 0.5f;

	// ���
	enum class STATE
	{
		NONE,
		PLAY,
		WARP_RESERVE,
		WARP_MOVE,
		DEAD,
		VICTORY,
		END
	};

	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		IDLE,
		RUN,
		FAST_RUN,
		JUMP,
		WARP_PAUSE,
		FLY,
		FALLING,
		VICTORY
	};

	Player(SceneManager* manager);
	void Init(void);
	void InitAnimation(void);
	void Update(void);
	void UpdatePlay(void);

	void Draw(void);
	void DrawShadow(void);
	void DrawDebug(void);

	void Release(void);

	void ProcessMove(void);

	void ProcessJump(void);

	void SetGoalRotate(double rotRad);
	void Rotate(void);

	void CalcGravityPow(void);

	void AddCollider(Collider* collider);
	void ClearCollider(void);

	Transform* GetTransform(void);

private:

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	// �A�j���[�V����
	AnimationController* mAnimationController;

	// ���
	STATE mState;

	// �ړ��X�s�[�h
	float mSpeed;

	// �ړ�����
	VECTOR mMoveDir;

	// �ړ���
	VECTOR mMovePow;

	VECTOR mMovedPos;

	Quaternion mPlayerRotY;

	Quaternion mGoalQuaRotY;

	float mStepRotTime;

	VECTOR mJumpPow;

	Capsule* mCapsule;

	bool mIsJump;

	float mStepJump;

	std::vector<Collider*> mColliders;

	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	int mImgShadow;

	// ��ԑJ��
	void ChangeState(STATE state);

	void Collision(void);
	void CollisionCapsule(void);
	void CollisionGravity(void);

	// ���n���[�V�����I��
	bool IsEndLanding(void);

};

