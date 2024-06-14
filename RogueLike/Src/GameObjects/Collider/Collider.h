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
    bool resistToforces = false;
protected:
    std::vector<CollisionElement *> collisionElemnets;
    bool solidObject = false;
    bool trigger = false;
    int mass = 1;
    bool mirror = false;

public:
    Collider();

    virtual ~Collider();

    void update(float deltaTime);

    void addForce(Vector2 dir, float power, float time);

    void clearForces() { allForces.clear(); }

    void isResistToForces(bool isResist);

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

    Vector2 getCollisionDir(Collider* collider);

#ifdef showColliders
    void draw();
#endif
    friend class GameScene;
    friend class Floor;
    friend class Controller;
private:
    void clearCollider();

    bool isColliding(Collider *collider, float deltaTime);

    void checkCollision(float deltaTime);

    void removeObject(Collider* c);
};
