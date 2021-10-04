#pragma once
#include <DxLib.h>

class SceneManager;
class Charactor;

class RollBall
{
public:
	RollBall(SceneManager* manager, Charactor* chara);
	~RollBall();
	void Init(void);
	void Update(void);
	void Draw(void);

private:
	SceneManager* mSceneManager;

	Charactor* chara_;
	VECTOR pos_;
	VECTOR angles_;
	VECTOR localAngles_;
	float zRad_;

	float delta_;
};

