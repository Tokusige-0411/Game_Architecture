#pragma once
#include <map>
#include <vector>
#include "Transform.h"
#include "IntVector3.h"

class SceneManager;
class ResourceManager;
class Rock;

class RockManager
{
public:
	RockManager();
	~RockManager();
	void Init(SceneManager* sManager, Transform* pTransform);
	void Update(void);
	void Draw(void);
	void Release(void);
	Rock* CreateRandom(IntVector3 map);

private:
	SceneManager* sceneManager_;
	ResourceManager* resourceManager_;
	Transform* playerTransform_;

	std::map<IntVector3, std::vector<Rock*>> rockMap_;
};

