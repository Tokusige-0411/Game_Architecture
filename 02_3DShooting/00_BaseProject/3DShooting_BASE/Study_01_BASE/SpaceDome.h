#pragma once
#include "Transform.h"

class SceneManager;

class SpaceDome
{
public:
	enum class State
	{
		Stay,
		Follow,
		Max
	};

	SpaceDome(SceneManager* manager, Transform* playerTrans);
	~SpaceDome();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void ChangeState(State state);

private:
	SceneManager* sceneManager_;

	// モデル制御の基本情報
	Transform transform_;
	Transform* playerTrans_;
	State state_;
};
