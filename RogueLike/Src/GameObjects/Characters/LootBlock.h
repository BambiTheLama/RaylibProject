#pragma once
#include "../GameObject.h"

extern const float tileW;
extern const float tileH;

class LootBlock :
    public GameObject
{
public:
    LootBlock(float x, float y);

    void draw();
};

