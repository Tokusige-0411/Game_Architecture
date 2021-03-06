#pragma once
#include <string>
#include <vector>

class Resource
{

public:

	enum class TYPE
	{
		NONE,
		IMG,
		IMGS,
		MODEL
	};

	Resource(void);
	Resource(TYPE type, std::string path);
	Resource(TYPE type, std::string path, int numX, int numY, int sizeX, int sizeY);
	Resource(Resource* base);

	void Load(void);
	void Release(void);

	void CopyHandle(int* imgs);

	TYPE mType;
	std::string mPath;

	// IMGS::LoadDivGraph用
	int mNumX;
	int mNumY;
	int mSizeX;
	int mSizeY;

	int mHandleId;
	int* mHandleIds;

	// モデル複製用
	std::vector<int> mDuplicateModelIds;

};

