#include "Collider.h"
#include "raylib.hpp"
#include "raymath.hpp"
#include <algorithm>
#include <cstdio>
#include "../Game.h"
#include "../../Core/WaveCollapsFun.h"
#include <math.h>

Collider::Collider(){
    thisObj = dynamic_cast<GameObject*>(this);
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

float getSpeedFromTime(float time)
{
    if (time >= 1)
        return 1.0f;

    return time * time;

        
}

void Collider::update(float deltaTime)
{
    for (auto c : collisionElemnets)
        c->update(thisObj);
    if (!thisObj)
        return;
    if (trigger)
    {
        for (auto f : allForces)
            delete f;
        allForces.clear();
        return;
    }
    const float constForce = 100;
    for (auto f : allForces)
    {
        float t = getSpeedFromTime(f->z);
        Vector2 dir = { f->x * deltaTime * t * constForce,f->y * deltaTime * t * constForce };
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

Vector2 Collider::getCollisionDir(Collider* collider)
{
    Vector2 pos = thisObj->getPosPoint();
    GameObject* otherObj = collider->getThisObj();
    if (!otherObj)
        return { 0,0 };
    Vector2 otherPos = otherObj->getPosPoint();
    for (auto c : collisionElemnets)
        for (auto c2 : collider->collisionElemnets)
            if (c->isCollidiongWith(pos, c2, otherPos)) {
                return c->getCollisionVectorDir(pos, c2, otherPos);
            }
    return { 0,0 };
}

bool Collider::isColliding(Collider *collider,float deltaTime) {
    Vector2 pos = thisObj->getPosPoint();
    GameObject* otherObj = collider->getThisObj();
    if (!otherObj)
        return false;
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
    Rectangle getCollsionArea = thisObj->getPos();
    getCollsionArea.width *= 2.5f;
    getCollsionArea.height *= 2.5f;
    getCollsionArea.x -= getCollsionArea.width/2;
    getCollsionArea.y -= getCollsionArea.height / 2;
    std::list<GameObject *> objects = Game::getObjects(getCollsionArea);
    objects.remove(thisObj);

    for (auto o: objects) {
        Collider *collider = dynamic_cast<Collider *>(o);
        if (!collider)
            continue;
        auto find = std::find(colliders.begin(), colliders.end(), collider);
        if (find != colliders.end())
            continue;
        if (isColliding(collider, deltaTime)) {
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

    if (!thisObj)
        return;
    for (auto o : allForces)
    {
        Rectangle pos = thisObj->getPos();
        Vector2 start = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
        float t = getSpeedFromTime(o->z);
        DrawLineEx(start, { start.x + o->x * 10 * t,start.y + o->y * 10 * t }, 5, BLACK);
    }

    for (auto c: collisionElemnets)
        c->draw(thisObj);
}
#endif

void Collider::removeObject(Collider* c) {
    lastFrameColliders.remove(c);
    colliders.remove(c);
}