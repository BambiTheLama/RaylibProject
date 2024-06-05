#pragma once
#include "raylib.hpp"
#include <vector>
#include <list>

#include "CollisionElement.h"


class GameObject;

class Collider {
    std::list<Collider *> colliders;
    std::list<Collider *> lastFrameColliders;
    GameObject* thisObj = nullptr;
    std::list<Vector3*> allForces;

protected:
    std::vector<CollisionElement *> collisionElemnets;
    bool solidObject = false;
    bool trigger = false;
    int mass = 1;
public:
    Collider();

    virtual ~Collider();

    void update(float deltaTime);

    void addForce(Vector2 dir, float power, float time);

    virtual void onCollisionEnter(Collider *collider) {
    }

    virtual void onCollision(Collider *collider) {
    }

    virtual void onCollisionExit(Collider *collider) {
    }

    virtual void onTriggerEnter(Collider* collider) {
    }

    virtual void onTrigger(Collider* collider) {
    }

    virtual void onTriggerExit(Collider* collider) {
    }

    bool isTrigger() { return trigger; }

    GameObject* getThisObj();

#ifdef showColliders
    void draw();
#endif
    friend class GameScene;
    friend class Floor;
    friend class Controller;
private:
    void clearCollider();

    bool isColliding(Collider *collider, GameObject *otherObj, float deltaTime);

    void checkCollision(float deltaTime);

    void removeObject(Collider* c);
};
