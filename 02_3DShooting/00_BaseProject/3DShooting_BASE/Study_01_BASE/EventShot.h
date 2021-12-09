#pragma once
#include "ShotBase.h"
#include "Transform.h"

class EventShot :
    public ShotBase
{
public:
    EventShot(SceneManager* manager, Transform* parent);

    void Update(void)override;

    float GetSpeed(void)override;
    float GetTimeAlive(void)override;
};

