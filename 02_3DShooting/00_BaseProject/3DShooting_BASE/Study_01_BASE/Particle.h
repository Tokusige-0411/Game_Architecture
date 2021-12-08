#pragma once

class SceneManager;

class Particle
{
public:
	Particle(SceneManager* manager, int image);
	void Generate(VECTOR pos, float size, VECTOR dir, float speed, float lifeTime);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	//Transform transform_;

	SceneManager* sceneManager_;
	int imageH_;

	VECTOR pos_;
	VECTOR dir_;
	float size_;
	float speed_;
	float lifeTime_;
};

