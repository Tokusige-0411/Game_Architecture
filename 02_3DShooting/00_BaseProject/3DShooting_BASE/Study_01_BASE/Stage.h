#pragma once
class SceneManager;

class Stage
{
public:
	static constexpr float RADIUS = 10000.0f;

	Stage(SceneManager* manager);
	~Stage();
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

	int GetModelID(void);

	VECTOR GetBossPos(void);

private:
	SceneManager* sceneManager_;

	int modelID_;
	VECTOR pos_;

	int bossModelID_;
	VECTOR bossPos_;
};
