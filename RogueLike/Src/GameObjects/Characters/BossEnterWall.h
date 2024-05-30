#pragma once
#include "../GameObject.h"

extern const float tileW;
extern const float tileH;

class BossEnterWall :
    public GameObject
{
public:
    BossEnterWall(float x, float y, float w = tileW, float h = tileH);
};

