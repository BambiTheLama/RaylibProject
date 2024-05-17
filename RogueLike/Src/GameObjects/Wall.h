#pragma once
#include "GameObject.h"
#include "AddisionalTypes/Collider/Collider.h"
#include "AddisionalTypes/Collider/CollisionElementBox.h"
#include "AddisionalTypes/Collider/CollisionElementLines.h"
#include "iostream"

class Wall : public GameObject, public Collider {
public:
    Wall(int x, int y) {
        pos = {(float) x, (float) y, 64.0f, 64.0f};

        //collisionElemnets.push_back(new CollisionElementBox({0, 0, pos.width, pos.height}));
        std::vector<Vector2> points = {{0, 0}, {0, 64}, {64, 0}};
        collisionElemnets.push_back(new CollisionElementLines(points));
    }

    void update(float deltaTime) {
    }

    void draw() override { DrawRectangleRec(pos,RED); }

    void onCollisionEnter(Collider *collider) override {
        printf("KURWA111\n");
    }

    void onCollisionExit(Collider *collider) override {
        printf("KURWA111 END\n");
    }
};
