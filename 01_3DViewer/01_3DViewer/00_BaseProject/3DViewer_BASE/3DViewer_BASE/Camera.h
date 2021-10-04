#pragma once
#include <DxLib.h>

class Charactor;

class Camera
{
public:
	Camera();
	~Camera();
	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	const VECTOR& GetPos(void)const;
	const VECTOR& GetAngles(void)const;

	void SetUnit(Charactor* chara);
	void SetTarget(const VECTOR& target);

private:
	VECTOR pos_;
	VECTOR angles_;

	Charactor* chara_;
	VECTOR target_;
	float speed_;
};

