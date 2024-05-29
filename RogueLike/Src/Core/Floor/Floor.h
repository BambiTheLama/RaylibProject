#pragma once
#include <list>
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/AddisionalTypes/Collider/Collider.h"
#include "../QuadTree.h"

class Room;
class Floor
{
    std::list<GameObject*> allGameObjects;
    std::list<GameObject*> closeObjects;
    std::list<GameObject*> toDelete;
    std::list<Collider*> colliders;
    std::list<Collider*> collidersToRemove;
    QuadTree* tree;
    Rectangle pos;
public:
    Floor(Rectangle pos);

    ~Floor();

    void setUpRooms(int startX, int startY, Room& room);

    void update(float deltaTime, Camera2D camera);

    void draw();

    std::list<GameObject*> getObjects(Rectangle pos);

    bool addObject(GameObject* obj);

    void deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);

};

