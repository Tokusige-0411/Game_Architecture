#pragma once
#include <memory>
#include "SceneBase.h"
class SceneManager;
class Stage;
class Charactor;
class RollBall;

class TitleScene : public SceneBase
{

public:
	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	std::unique_ptr<Stage> stage_;
	std::shared_ptr<Charactor> charactor_;
	std::shared_ptr<RollBall> ball_;
};
