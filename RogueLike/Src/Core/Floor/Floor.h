#pragma once
#include <list>
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/Collider/Collider.h"
#include "../QuadTree.h"
#include <vector>
#include "../WaveCollapsFun.h"
#include "PathFinder.h"
class Room;
using CreateObjectFun = GameObject * (*)(int, Rectangle);

class Floor
{
    std::list<GameObject*> allGameObjects;
    std::list<GameObject*> closeObjects;
    std::list<GameObject*> toDelete;
    std::list<GameObject*> toRemove;
    std::list<GameObject*> toAdd;
    std::list<Collider*> colliders;
    PathFinder* pathFinder = nullptr;
    QuadTree* tree;
    Rectangle pos;
    Rectangle startPos = { 0,0,32,32 };
    Rectangle endPos = { 0,0,32,32 };
    int seed = 0;
public:
    Floor(Rectangle pos, int seed = 0);

    ~Floor();

    void createFloor();

    void start();

    void setUpRooms(int startX, int startY, Room& room);

    void update(float deltaTime, Camera2D camera);

    void draw();

    void drawUI();

    std::list<GameObject*> getObjects(Rectangle pos);

    bool addObject(GameObject* obj);

    bool deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);

    Vector2 getDirToGo(Rectangle start, Rectangle end, float range) { return pathFinder->getDirToGo(start, end, range); }

    std::list<Vector3> getPathToGo(Rectangle start, Rectangle end, float range) { return pathFinder->getPathToGo(start, end, range); }

    void toCheckPos(Rectangle toCheck);

    bool canPassMap();

    bool isObjectAtScene(GameObject* gm);

private:
    void setUpObjects(std::vector<int> objects, int numberOfObjects, BlockType type, std::vector<std::vector<RoomData>>& roomGrid, CreateObjectFun fun, int rangeW = 10, int rangeH = 10);

    void removeCloseEnemies();

    void removeObj(GameObject* o);

    void setSeeds();
};

