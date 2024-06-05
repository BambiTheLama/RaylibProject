#include "Collider.h"
#include "raylib.hpp"
#include "raymath.hpp"
#include <algorithm>
#include <cstdio>
#include "../../GameObject.h"
#include "../../Game.h"
#include "../../../Core/WaveCollapsFun.h"

Collider::Collider(){

}

Collider::~Collider() {
    for (auto c: collisionElemnets)
        delete c;
    collisionElemnets.clear();
    for (auto f : allForces)
        delete f;
}

bool removeIf(Vector3* vec)
{
    if (vec->z <= 0.0f)
    {
        delete vec;
        return true;
    }
    return false;
}

void Collider::update(float deltaTime)
{
    if (!thisObj)
        return;
    const float constForce = 100;
    for (auto f : allForces)
    {
        Vector2 dir = { f->x * deltaTime * f->z * constForce,f->y * deltaTime * f->z * constForce };
        thisObj->move(dir);
        f->z -= deltaTime*3;
    }
    allForces.remove_if(removeIf);
}

void Collider::addForce(Vector2 dir, float power,float time)
{
    dir = Vector2Normalize(dir);
    allForces.push_back(new Vector3{ dir.x*power, dir.y*power, time });
}

GameObject* Collider::getThisObj()
{
    if (!thisObj) 
        thisObj = dynamic_cast<GameObject*>(this);
    
    return thisObj;
    
}

void Collider::clearCollider() {
    std::vector<Collider *> collidersExit;

    for (auto c: lastFrameColliders) {
        auto find = std::find(colliders.begin(), colliders.end(), c);
        if (find == colliders.end())
            collidersExit.push_back(c);
    }
    lastFrameColliders = colliders;
    colliders.clear();
    for (auto c : collidersExit)
    {
        onCollisionExit(c);
    }

}


bool Collider::isColliding(Collider *collider, GameObject *otherObj,float deltaTime) {
    Vector2 pos = thisObj->getPosPoint();
    Vector2 otherPos = otherObj->getPosPoint();
    for (auto c: collisionElemnets)
        for (auto c2: collider->collisionElemnets)
            if (c->isCollidiongWith(pos, c2, otherPos)) {

                if (trigger || collider->trigger)
                    return true;
                float massAdd = mass + collider->mass;
                Vector2 dirVector = c->getCollisionVectorDir(pos, c2, otherPos);

                const float moveMultyplay = 0.02f;



                if (!solidObject)
                {
                    float speed = thisObj->getSpeed();
                    if (speed <= 0)
                        speed = 1;
                    thisObj->pos.x += dirVector.x * (collider->mass / massAdd) * moveMultyplay * speed;
                    thisObj->pos.y += dirVector.y * (collider->mass / massAdd) * moveMultyplay * speed;
                }

                if (!collider->solidObject)
                {
                    float speed = otherObj->getSpeed();
                    if (speed <= 0)
                        speed = 1;
                    otherObj->pos.x -= dirVector.x * (mass / massAdd) *  moveMultyplay * speed;
                    otherObj->pos.y -= dirVector.y * (mass / massAdd) *  moveMultyplay * speed;
                }
                
                return true;
            }


    return false;
}


void Collider::checkCollision(float deltaTime) {
    if (!thisObj) {
        thisObj = dynamic_cast<GameObject*>(this);
        if (!thisObj)
            return;
    }

    std::list<GameObject *> objects = Game::getObjects(thisObj->getPos());
    objects.remove(thisObj);

    for (auto o: objects) {
        Collider *collider = dynamic_cast<Collider *>(o);
        if (!collider)
            continue;
        auto find = std::find(colliders.begin(), colliders.end(), collider);
        if (find != colliders.end())
            continue;
        if (isColliding(collider, o,deltaTime)) {
            find = std::find(lastFrameColliders.begin(), lastFrameColliders.end(), collider);
            if (find == lastFrameColliders.end()) {
                if (trigger || collider->trigger)
                {
                    if (trigger)
                        onTriggerEnter(collider);
                    if (collider->trigger)
                        collider->onTriggerEnter(this);
                }
                else
                {
                    onCollisionEnter(collider);
                    collider->onCollisionEnter(this);
                }
            } else {
                if (trigger || collider->trigger)
                {
                    if (trigger)
                        onTrigger(collider);
                    if (collider->trigger)
                        collider->onTrigger(this);
                }
                else
                {
                    onCollision(collider);
                    collider->onCollision(this);
                }

            }
            collider->colliders.push_back(this);
            colliders.push_back(collider);
        }
    }
}


#ifdef showColliders

void Collider::draw() {
    GameObject *obj = dynamic_cast<GameObject *>(this);

    for (auto c: collisionElemnets)
        c->draw(obj);
}
#endif

void Collider::removeObject(Collider* c) {
    lastFrameColliders.remove(c);
    colliders.remove(c);
}