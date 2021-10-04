#pragma once
#include <DxLib.h>

class SceneManager;
class Charactor;

class Enemy
{
public:
	Enemy(SceneManager* manager, Charactor* chara);
	~Enemy();
	void Init(void);
	void Update(void);
	void Draw(void);

private:
	SceneManager* mSceneManager;

	Charactor* chara_;
	VECTOR pos_;
};

