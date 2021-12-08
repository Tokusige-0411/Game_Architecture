#pragma once
#include "Transform.h"

class SceneManager;
class SpriteAnimator;
class SpeechBalloon;

enum class PlayerState
{
	Normal,
	Destroy,
};

class GoldShip
{
public:
	static constexpr float COLLISION_RADIUS = 20.0f;

	GoldShip(SceneManager* manager);
	~GoldShip();
	void Init(void);
	void Update(void);
	void UpdateNormal(void);
	void UpdateDestroy(void);
	void Draw(void);
	void Release(void);

	void ProcessTurn(void);
	void Turn(float deg, VECTOR axis);

	Transform* GetTransform(void);

	void ChangeState(PlayerState state);
	PlayerState GetState(void);

	bool IsDestoy(void);

	SpeechBalloon* GetSpeechBalloon(void);

private:

	SceneManager* sceneManager_;
	// モデル制御の基本情報
	Transform transform_;

	PlayerState state_;

	SpriteAnimator* animator_;

	bool isDestroy_;

	SpeechBalloon* sBalloon_;
};
