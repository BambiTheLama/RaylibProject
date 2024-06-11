#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../Collider/CollisionElementLines.h"

class BossWall :
    public GameObject , public Collider
{
    BossWall();
public:
    BossWall(float x, float y);

    BossWall(int x, int y, int w, int h);

    void update(float deltaTime);

    void draw();
};

