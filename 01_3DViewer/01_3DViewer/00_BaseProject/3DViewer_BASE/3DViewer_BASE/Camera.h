#pragma once
#include <DxLib.h>

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

private:
	VECTOR pos_;
	VECTOR angles_;
	float speed_;
};

