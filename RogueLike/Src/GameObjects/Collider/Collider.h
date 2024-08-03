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
    std::vector<CollisionElement*> collisionElements;
    bool resistToforces = false;
protected:
    Vector2 difSize = { 1.0f,1.0f };
    bool fHorizontal = false;
    bool solidObject = false;
    bool trigger = false;
    int mass = 1;
    bool mirror = false;
    bool reactOnlyToSolid = false;
    bool scale = 1.0f;
public:
    Collider();

    virtual ~Collider();

    void update(float deltaTime);

    void addForce(Vector2 dir, float power, float time);

    void clearForces() { allForces.clear(); }

    void setResistToForces(bool isResist);

    void setReactOnlyToSolid(bool reactOnlyToSolid) { this->reactOnlyToSolid = reactOnlyToSolid; }

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

    void scaleColliderElements(float scale);

    void flipHorizontalElements(bool flipHorizontal);

    bool isTrigger() { return trigger; }

    bool isSolidObject() { return solidObject; }

    GameObject* getThisObj();

    Vector2 getCollisionDir(Collider* collider);

    bool isColliderToRemove();

    void addCollisionElement(CollisionElement* element) { collisionElements.push_back(element); }

    void clearCollisionElements();

#ifdef showColliders
    void draw();
#endif
    friend class GameScene;
    friend class Floor;
    friend class Controller;
private:
    void clearCollider();

    void overlapMove(Collider* collider, Vector2 dir, float fullMass, float dist);

    bool isColliding(Collider *collider, float deltaTime);

    void checkCollision(float deltaTime);

    Rectangle getCollisionArea(Rectangle pos);

    void removeObject(Collider* c);
};
