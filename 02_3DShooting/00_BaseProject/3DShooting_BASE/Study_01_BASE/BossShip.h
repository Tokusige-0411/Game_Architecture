#pragma once
#include "Transform.h"

class SceneManager;
class GoldShip;

enum class BossState
{
	Event,
	Battle,
	Destroy
};

class BossShip
{
public:
	BossShip(SceneManager* manager, GoldShip* player);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	SceneManager* sceneManager_;
	GoldShip* playerShip_;
	Transform transform_;

	BossState state_;
};
