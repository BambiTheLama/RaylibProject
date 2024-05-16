#pragma once
#include "raylib.h"
#include <vector>
#include <list>

#include "CollisionElement.h"
class GameObject;

class Collider {
    std::list<Collider *> colliders;
    std::list<Collider *> lastFrameColliders;
    std::vector<CollisionElement *> collisionElemnets;

public:
    virtual void onCollisionEnter(Collider *collider) {
    }

    virtual void onCollision(Collider *collider) {
    }

    virtual void onCollisionExit(Collider *collider) {
    }

private:
    void clearCollider();

    bool isColliding(GameObject *thisObj, Collider *collider, GameObject *otherObj);

    void checkCollision();
};

