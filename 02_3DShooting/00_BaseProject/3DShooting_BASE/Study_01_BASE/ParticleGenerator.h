#pragma once
#include <array>

class SceneManager;
class Particle;

class ParticleGenerator
{
public:

	ParticleGenerator(SceneManager* manager, VECTOR pos, float radius);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawMeshSquare(void);
	void DrawMeshCIrcle(void);
	void Release(void);

private:
	Particle* Generate(Particle* particle);

	SceneManager* sceneManager_;
	VECTOR pos_;

	float radius_;

	// éläp
	std::array<VERTEX3D, 6> square_;

	// â~
	std::array<VERTEX3D, 11> circle_;
	std::array<WORD, 30> circleIndex_;

	int lightH_;

	std::array<Particle*, 20> particle_;

	void CreateSquareVertex(void);
	void CreateCircleVertex(void);

};
