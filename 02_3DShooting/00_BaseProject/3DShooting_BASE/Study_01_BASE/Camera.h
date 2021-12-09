#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"
class SceneManager;
class Transform;

class Camera
{

public:

	// カメラの初期座標
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

	// カメラ位置と注視点との相対座標
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -100.0f, 500.0f };

	// ﾌﾟﾚｲﾔｰからのカメラの位置
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0f, 25.0f, -80.0f };

	// ﾌﾟﾚｲﾔｰからのカメラの位置
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

	// カメラモード変更
	void ChangeMode(MODE mode);

	// 自機の設定
	void SetShip(Transform* ship);

private:

	SceneManager* mSceneManager;
	Transform* shipTransform_;

	// カメラモード
	MODE mMode;

	// カメラの位置
	VECTOR mPos;

	// カメラ角度
	Quaternion mQuaRot;

	// 注視点
	VECTOR mTargetPos;

	// カメラの上方向
	VECTOR mCameraUp;

	VECTOR mVelocity;

	float stepShake_;
	VECTOR shakeDir_;
	VECTOR defaultPos;
};

