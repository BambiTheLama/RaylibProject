#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../Collider/CollisionElementLines.h"
#include "iostream"
#include "../AddisionalTypes/Hitable.h"
#include <vector>

extern const float tileW;
extern const float tileH;

class Wall : public GameObject, public Collider{

public:
    Wall(float x, float y, float w = tileW, float h = tileH);

    ~Wall();

    void update(float deltaTime);

    void draw() override;

    void onCollisionEnter(Collider* collider) override;

    void onCollisionExit(Collider* collider) override;
};
