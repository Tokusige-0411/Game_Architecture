#pragma once
#include "DxLib.h"
#include "Quaternion.h"

class SceneManager;

class Coin
{

public:

	enum class Type
	{
		Vector,
		Matrix,
		Quaternion,
		Max,
	};

	Coin(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);

	void SetModelVector(void);

	void SetModelMatrix(void);

	void SetModelQuaternion(void);

	void DrawDirection(void);

private:

	// ÉÇÉfÉãID
	int modelID_;

	// ç¿ïW
	VECTOR pos_;

	VECTOR angles_;
	VECTOR localAngles_;

	Type updateType_;

	MATRIX matScl_;
	MATRIX matRot_;
	MATRIX matRotLocal_;
	MATRIX matTrn_;

	Quaternion quaRotLocal_;
};

