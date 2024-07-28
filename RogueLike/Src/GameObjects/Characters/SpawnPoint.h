#pragma once
#include "../GameObject.h"
#include "../../Core/BlockType.h"

extern const float tileW;
extern const float tileH;

class SpawnPoint :
    public GameObject
{
    BlockType type;
public:
    SpawnPoint(float x, float y, BlockType type);

    void update(float deltaTime);

    BlockType getType() { return type; }

    void draw() { DrawRectangleRec(pos, { 0,0,128,128 }); }
};

