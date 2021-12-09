#pragma once
#include <vector>
#include "SceneBase.h"

class SceneManager;
class SpaceDome;
class Stage;
class GoldShip;

class GameScene : public SceneBase
{

public:

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	SpaceDome* spaceDome_;
	Stage* stage_;
	GoldShip* playerShip_;
};
