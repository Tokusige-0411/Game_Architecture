#pragma once
#include "SceneBase.h"

class SpaceDome;
class ParticleGenerator;
class TextScroll;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawLogo(void);
	void Release(void) override;

private:

	int mImgStartLogo;
	SpaceDome* spaceDome_;
	ParticleGenerator* particleGenerator_;
	TextScroll* textScroll_;
};

