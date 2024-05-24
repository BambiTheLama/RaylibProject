#include "Floor.h"
#include "../WaveCollapsFun.h"
#include "Room.h"
#include "RoomElements.h"

Floor::Floor(Rectangle pos)
{
    this->pos = pos;
    tree = new QuadTree(pos);
    FloorRooms floorRooms;
    for (int i = 0; i < 8; i++)
        floorRooms.standardsRooms.push_back(getRoom(i).createRoomData());
    int floorW = 10;
    int floorH = 10;
    std::vector<std::vector<RoomData>> roomGrid = generareFloor(floorW, floorH, floorRooms);
    for (int i = 0; i < floorW; i++)
        for (int j = 0; j < floorH; j++)
        {
            int startX = roomW * i;
            int startY = roomH * j;
            int ID = roomGrid[j][i].ID;
            if (ID < 0)
                continue;
            Room room = getRoom(ID);

            for (int x = 0; x < roomSize; x++)
                for (int y = 0; y < roomSize; y++)
                {
                    GameObject* b = getRoomElement(room.getBlockID(x, y), startX + x * tileW, startY + y * tileH);
                    if (b)
                        addObject(b);
                }
        }
}

Floor::~Floor()
{
    for (auto o : gameObjects)
        deleteObject(o);
    colliders.clear();
    for (auto o : toDelete)
    {
        gameObjects.remove(o);
        Collider* collider = dynamic_cast<Collider*>(o);
        if (collider) {
            colliders.remove(collider);
            for (auto c : colliders)
                c->removeObject(collider);
        }
        delete o;
    }

    toDelete.clear();
    delete tree;
}

bool sortGameObjectCondiction(GameObject* gm, GameObject* gm2)
{
    if (gm->getDrawOrder() == gm2->getDrawOrder())
    {
        Rectangle r1 = gm->getPos();
        Rectangle r2 = gm2->getPos();
        return r1.y + r1.height < r2.y + r2.height;
    }
    return gm->getDrawOrder() < gm2->getDrawOrder();
}

void Floor::update(float deltaTime)
{

    if (IsKeyPressed(KEY_F1))
        for (auto o : gameObjects)
            deleteObject(o);
    for (auto o : toDelete)
    {
        gameObjects.remove(o);
        Collider* collider = dynamic_cast<Collider*>(o);
        if (collider) {
            colliders.remove(collider);
            for (auto c : colliders)
                c->removeObject(collider);
        }
        delete o;
    }

    toDelete.clear();
    for (auto o : gameObjects)
        o->update(deltaTime);
    tree->update();

    for (auto o : colliders)
        o->clearCollider();
    for (auto o : colliders)
        o->checkCollision(deltaTime);
    for (auto c : collidersToRemove)
        colliders.remove(c);
    collidersToRemove.clear();
    gameObjects.sort(sortGameObjectCondiction);

}

void Floor::draw()
{
    for (auto o : gameObjects)
    {
        o->draw();
    }

#ifdef showColliders
    for (auto o : colliders) {
        o->draw();
    }
#endif
    if (IsKeyDown(KEY_TAB))
        tree->draw();
}

std::list<GameObject*> Floor::getObjects(Rectangle pos) 
{
	return tree->getObjects(pos); 
}

bool Floor::addObject(GameObject* obj)
{
    auto find = std::find(gameObjects.begin(), gameObjects.end(), obj);
    if (find != gameObjects.end())
        return true;
    gameObjects.push_back(obj);
    Collider* collider = dynamic_cast<Collider*>(obj);
    if (collider)
    {
        if (!collider->solidObject)
            colliders.push_back(collider);
        tree->addObj(obj);
    }

    return true;
}

void Floor::deleteObject(GameObject* obj)
{
    removeObject(obj);
    toDelete.push_back(obj);
}

void Floor::removeObject(GameObject* obj)
{
    Collider* collider = dynamic_cast<Collider*>(obj);
    if (collider) {
        collidersToRemove.remove(collider);
    }
    tree->removeObj(obj);
}