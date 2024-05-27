#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Collider/Collider.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "../AddisionalTypes/Collider/CollisionElementLines.h"
class BossWall :
    public GameObject , public Collider
{
public:
    BossWall(int x, int y);

    void update(float deltaTime);

    void draw();
};

