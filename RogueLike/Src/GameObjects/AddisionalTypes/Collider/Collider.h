#pragma once
#include "raylib.h"
#include <vector>
#include <list>

#include "CollisionElement.h"


class GameObject;

class Collider {
    std::list<Collider *> colliders;
    std::list<Collider *> lastFrameColliders;
    GameObject* thisObj = nullptr;


protected:
    std::vector<CollisionElement *> collisionElemnets;
    bool solidObject = false;
    bool trigger = false;
    int mass = 1;
public:
    Collider();

    virtual ~Collider();

    virtual void onCollisionEnter(Collider *collider) {
    }

    virtual void onCollision(Collider *collider) {
    }

    virtual void onCollisionExit(Collider *collider) {
    }

    bool isTrigger() { return trigger; }

    GameObject* getThisObj();



#ifdef showColliders
    void draw();
#endif
    friend class GameScene;
private:
    void clearCollider();

    bool isColliding(Collider *collider, GameObject *otherObj);

    void checkCollision();

    void removeObject(Collider* c);
};
