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
	
	int modelID_;
	Charactor* chara_;
	VECTOR pos_;
	VECTOR angles_;
	VECTOR localAngles_;
};

