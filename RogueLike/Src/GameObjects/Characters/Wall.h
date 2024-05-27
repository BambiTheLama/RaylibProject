#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Collider/Collider.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "../AddisionalTypes/Collider/CollisionElementLines.h"
#include "iostream"
#include "../AddisionalTypes/Hitable.h"


class Wall : public GameObject, public Collider, public Hitable {
public:
    Wall(int x, int y);

    Wall(int x, int y, int w, int h);

    void update(float deltaTime);

    void draw() override;

    void onCollisionEnter(Collider* collider) override;

    void onCollisionExit(Collider* collider) override;
};
