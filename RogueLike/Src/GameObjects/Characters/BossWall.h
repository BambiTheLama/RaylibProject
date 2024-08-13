#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../Collider/CollisionElementLines.h"

class BossWall :
    public GameObject , public Collider
{
    TextureController texture;
    BossWall();
public:
    BossWall(float x, float y);

    BossWall(float x, float y, float w, float h);

    void start() override;

    void update(float deltaTime);

    void draw();
};

