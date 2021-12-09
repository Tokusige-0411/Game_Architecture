#pragma once
#include "ShotBase.h"

class SceneManager;
class Transform;

class TurretShot :
    public ShotBase
{
public:
    TurretShot(SceneManager* manager, Transform* parent);
};

