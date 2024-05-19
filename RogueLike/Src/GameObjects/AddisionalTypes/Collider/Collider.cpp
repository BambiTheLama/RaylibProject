#include "Collider.h"
#include "raymath.h"
#include <algorithm>
#include <cstdio>
#include "../../GameObject.h"
#include "../../Game.h"


Collider::Collider(){

}

Collider::~Collider() {
    for (auto c: collisionElemnets)
        delete c;
    collisionElemnets.clear();
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


bool Collider::isColliding(Collider *collider, GameObject *otherObj) {
    Vector2 pos = thisObj->getPosPoint();
    Vector2 otherPos = otherObj->getPosPoint();
    for (auto c: collisionElemnets)
        for (auto c2: collider->collisionElemnets)
            if (c->isCollidiongWith(pos, c2, otherPos)) {

                    
                ///TODO POPRAWIC DZia³anie

                Vector2 dirVector = pos - otherPos;

                dirVector = Vector2Normalize(dirVector);
                if (abs(dirVector.x) < abs(dirVector.y))
                    dirVector.x = 0;
                else
                    dirVector.y = 0;

                if (!solidObject)
                {
                    thisObj->pos.x += dirVector.x;
                    thisObj->pos.y += dirVector.y;
                }

                if (!collider->solidObject)
                {
                    otherObj->pos.x -= dirVector.x;
                    otherObj->pos.y -= dirVector.y;
                }
                
                return true;
            }


    return false;
}


void Collider::checkCollision() {
    if (!thisObj) {
        thisObj = dynamic_cast<GameObject*>(this);
        if (!thisObj)
            return;
    }

    std::list<GameObject *> objects = Game::getObjects(thisObj->getPos());
    while(std::find(objects.begin(), objects.end(), thisObj) != objects.end())
        objects.remove(thisObj);
    for (auto o: objects) {
        Collider *collider = dynamic_cast<Collider *>(o);
        if (!collider)
            continue;
        auto find = std::find(colliders.begin(), colliders.end(), collider);
        if (find != colliders.end())
            continue;
        if (isColliding(collider, o)) {
            find = std::find(lastFrameColliders.begin(), lastFrameColliders.end(), collider);
            if (find == lastFrameColliders.end()) {
                onCollisionEnter(collider);
                collider->onCollisionEnter(this);
            } else {
                onCollision(collider);
                collider->onCollision(this);
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