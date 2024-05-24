#pragma once
#include <list>
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/AddisionalTypes/Collider/Collider.h"
#include "../QuadTree.h"

class Floor
{
    std::list<GameObject*> gameObjects;
    std::list<GameObject*> toDelete;
    std::list<Collider*> colliders;
    std::list<Collider*> collidersToRemove;
    QuadTree* tree;
    Rectangle pos;
public:
    Floor(Rectangle pos);

    ~Floor();

    void update(float deltaTime);

    void draw();

    std::list<GameObject*> getObjects(Rectangle pos);

    bool addObject(GameObject* obj);

    void deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);

};

