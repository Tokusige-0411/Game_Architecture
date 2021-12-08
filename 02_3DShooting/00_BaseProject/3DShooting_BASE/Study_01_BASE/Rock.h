#pragma once
#include "Transform.h"

class Rock
{
public:
	Rock();
	~Rock();
	void Init(int modelID, VECTOR pos, VECTOR angle, VECTOR scale);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

private:
	Transform transform_;
};

