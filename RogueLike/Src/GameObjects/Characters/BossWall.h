#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../Collider/CollisionElementLines.h"
#include "../AddisionalTypes/ShadowObject.h"
class BossWall :
    public GameObject , public Collider,public ShadowObject
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

