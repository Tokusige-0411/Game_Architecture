#pragma once
#include <vector>
#include "Transform.h"

class SceneManager;
class SpriteAnimator;
class SpeechBalloon;
class ParticleGenerator;
class PlayerShot;

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
	void ProcessShot(void);

	Transform* GetTransform(void);

	void ChangeState(PlayerState state);
	PlayerState GetState(void);

	bool IsDestoy(void);

	SpeechBalloon* GetSpeechBalloon(void);

	std::vector<PlayerShot*> GetPlayerShot(void);

private:

	SceneManager* sceneManager_;

	// ÉÇÉfÉãêßå‰ÇÃäÓñ{èÓïÒ
	Transform transform_;

	PlayerState state_;

	SpriteAnimator* animator_;

	bool isDestroy_;

	SpeechBalloon* sBalloon_;

	ParticleGenerator* particleGenerator_;

	std::vector<PlayerShot*> playerShots_;

	float deleyShot_;

	void CreateShot(void);
};
