#pragma once
#include "../GameObject.h"

extern enum class BlockType :char;
extern const float tileW;
extern const float tileH;

class SpawnPoint :
    public GameObject
{
    BlockType type;
public:
    SpawnPoint(float x, float y, BlockType type);

    BlockType getType() { return type; }

    void draw() { DrawRectangleRec(pos, { 0,0,128,128 }); }
};

