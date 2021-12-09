#pragma once
#include "SceneBase.h"

class BossShip;
class SpaceDome;
class RockManager;
class GoldShip;

class BattleScene :
    public SceneBase
{
public:

	BattleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//RockManager* rockManager_;
	GoldShip* playerShip_;
	BossShip* bossShip_;
	SpaceDome* spaceDome_;
};

