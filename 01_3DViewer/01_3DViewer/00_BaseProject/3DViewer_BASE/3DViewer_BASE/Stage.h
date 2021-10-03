#pragma once

class SceneManager;

class Stage
{
public:
	Stage(SceneManager* manager);
	~Stage();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	SceneManager* mSceneManager;

	// ���f���̃n���h��
	int modelID_;
	VECTOR pos_;
};

