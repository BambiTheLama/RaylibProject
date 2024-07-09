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
        c->update(thisObj, mirror);
    if (!thisObj)
        return;

    for (auto f : allForces)
    {
        float t = getSpeedFromTime(f->z) * deltaTime*100.0f/ mass;
        Vector2 dir = { f->x * t ,f->y * t };
        float len = Vector2Length(dir);
        if (len > 16)
        {
            dir = Vector2Scale(Vector2Normalize(dir), 16);
        }
        thisObj->move(dir);
        f->z -= deltaTime;
    }
    allForces.remove_if(removeIf);
}

void Collider::addForce(Vector2 dir, float power,float time)
{
    if (resistToforces)
        return;
    dir = Vector2Normalize(dir);
    allForces.push_back(new Vector3{ dir.x*power, dir.y*power, time });
}

void Collider::isResistToForces(bool isResist)
{
    if (isResist)
    {
        this->resistToforces = isResist;
        allForces.clear();
    }
}

void Collider::scaleColliderElements(float scale)
{
    for (auto e : collisionElemnets)
        e->scaleElement(scale);
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
        {
            Vector2 dir;
            float dist;
            if (c->isCollidiongWith(pos, c2, otherPos, &dir, &dist)) {
                return dir;
            }
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
        for (auto c2 : collider->collisionElemnets)
        {
            Vector2 dir;
            float dist;
            if (c->isCollidiongWith(pos, c2, otherPos, &dir, &dist)) {

                if (trigger || collider->trigger)
                    return true;
                float massAdd = (float)mass + collider->mass;

                if (!solidObject)
                {
                    float massMove = 1;
                    if (!collider->solidObject)
                        massMove = (collider->mass / massAdd);
                    thisObj->pos.x += dir.x * massMove * dist;
                    thisObj->pos.y += dir.y * massMove * dist;
                }

                if (!collider->solidObject)
                {
                    float massMove = 1;
                    if (!solidObject)
                        massMove = (mass / massAdd);
                    otherObj->pos.x -= dir.x * massMove * dist;
                    otherObj->pos.y -= dir.y * massMove * dist;
                }

                return true;
            }
        }
            


    return false;
}


void Collider::checkCollision(float deltaTime) {
    if (!thisObj) {
        thisObj = dynamic_cast<GameObject*>(this);
        if (!thisObj)
            return;
    }
    Rectangle collsionArea = getCollisionArea(thisObj->getPos());
    std::list<GameObject *> objects = Game::getObjects(collsionArea);
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

Rectangle Collider::getCollisionArea(Rectangle pos)
{
    Vector2 minV = collisionElemnets[0]->getMinPos();
    Vector2 maxV = collisionElemnets[0]->getMaxPos();
    for (int i = 1; i < collisionElemnets.size(); i++)
    {
        CollisionElement* e = collisionElemnets[i];
        Vector2 tmp = e->getMinPos();
        if (tmp.x < minV.x)
            minV.x = tmp.x;
        if (tmp.y < minV.y)
            minV.y = tmp.y;
        tmp = e->getMaxPos();
        if (tmp.x > maxV.x)
            maxV.x = tmp.x;
        if (tmp.y > maxV.y)
            maxV.y = tmp.y;

    }
    return { pos.x + minV.x,pos.y + minV.y,maxV.x - minV.x,maxV.y - minV.y };
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
        DrawLineEx(start, { start.x + o->x/mass * 10 * t,start.y + o->y/mass * 10 * t }, 5, BLACK);
    }
    DrawRectangleRec(getCollisionArea(thisObj->getPos()), { 0,0,255,100 });

    for (auto c: collisionElemnets)
        c->draw(thisObj);
}
#endif

void Collider::removeObject(Collider* c) {
    lastFrameColliders.remove(c);
    colliders.remove(c);
}