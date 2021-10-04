#pragma once
#include <DxLib.h>

class SceneManager;

class Charactor
{
public:
	Charactor(SceneManager* manager);
	~Charactor();
	void Init(void);
	void Update(void);
	void Draw(void);

	const VECTOR& GetPos(void);
	const VECTOR& GetAngles(void);

private:
	SceneManager* mSceneManager;

	int modelID_;
	VECTOR pos_;
	VECTOR angles_;
	VECTOR localAngles_;
	float speed_;

	int animID_;
	float totalAnimTime_;
	float animTime_;
};

