#pragma once
#include "ShotBase.h"

class SceneManager;
class Transform;

class PlayerShot :
    public ShotBase
{
public:
    PlayerShot(SceneManager* manager, Transform* parent);


};

