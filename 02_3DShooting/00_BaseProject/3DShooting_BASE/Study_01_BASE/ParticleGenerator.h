#pragma once
#include <array>
#include <vector>

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

	void SetPos(VECTOR pos);
	void SetRot(Quaternion rot);

private:
	SceneManager* sceneManager_;
	VECTOR pos_;
	Quaternion quaRot_;

	float radius_;

	// éläp
	std::array<VERTEX3D, 6> square_;

	// â~
	std::array<VERTEX3D, 11> circle_;
	std::array<WORD, 30> circleIndex_;

	int lightH_;
	float stepGenetare_;

	std::vector<Particle*> particle_;

	Particle* Generate(Particle* particle);
	void CreateSquareVertex(void);
	void CreateCircleVertex(void);

};
