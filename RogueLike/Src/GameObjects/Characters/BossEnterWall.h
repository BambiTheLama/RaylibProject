#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../../Core/BlockType.h"

extern const float tileW;
extern const float tileH;

class BossEnterWall :
    public GameObject, public Collider
{
    static bool wasEnter;
    static bool openDoor;
    bool hasSpawnPoint = false;
    Vector2 spawnPoint;
public:
    BossEnterWall(float x, float y, float w = tileW, float h = tileH);

    void start();

    void draw();

    void onCollisionEnter(Collider* collider) override;
};

