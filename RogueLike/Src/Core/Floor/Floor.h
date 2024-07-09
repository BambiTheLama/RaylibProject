#pragma once
#include <list>
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/Collider/Collider.h"
#include "../QuadTree.h"
#include <vector>
#include "../WaveCollapsFun.h"

class Room;


class Floor
{
    std::list<GameObject*> allGameObjects;
    std::list<GameObject*> closeObjects;
    std::list<GameObject*> toDelete;
    std::list<GameObject*> toRemove;
    std::list<Collider*> colliders;
    QuadTree* tree;
    Rectangle pos;
public:
    Floor(Rectangle pos);

    ~Floor();

    void start();

    void setUpRooms(int startX, int startY, Room& room);

    void update(float deltaTime, Camera2D camera);

    void draw();

    void drawUI();

    std::list<GameObject*> getObjects(Rectangle pos);

    bool addObject(GameObject* obj);

    void deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);

private:
    void setUpObjects(std::vector<int> objects, int numberOfObjects, BlockType type, std::vector<std::vector<RoomData>>& roomGrid);

    void removeCloseEnemies();

};

