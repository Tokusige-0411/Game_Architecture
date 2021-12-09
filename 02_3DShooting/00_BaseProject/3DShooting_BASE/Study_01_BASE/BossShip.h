#pragma once
#include <vector>
#include "Transform.h"

class SceneManager;
class GoldShip;
class EventShot;
class Turret;

enum class BossState
{
	Event,
	Battle,
	Destroy,
	End
};

class BossShip
{
public:
	static constexpr float speed_move = 4.0f;
	static constexpr float event_time = 4.0f;

	BossShip(SceneManager* manager, GoldShip* player);
	void Init(void);
	void Update(void);
	void UpdateTurret(void);
	void Draw(void);
	void DrawTurret(void);
	void Release(void);

	Transform GetTransform(void);

	std::vector<Turret*> GetTurrets(void);

private:
	SceneManager* sceneManager_;
	GoldShip* playerShip_;

	EventShot* eventShot_;

	Transform transform_;

	BossState state_;

	float stepEvent_;

	std::vector<Turret*> turrets_;

	void ChangeState(BossState state);

	void MakeTurret(VECTOR localPos, VECTOR localAddAxis);
};
