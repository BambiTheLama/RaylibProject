#include "Floor.h"
#include "../WaveCollapsFun.h"
#include "Room.h"
#include "RoomElements.h"
#include <fstream>
#include "../../GameObjects/Characters/Wall.h"

FloorRooms getFloorRooms()
{
    FloorRooms floorRooms;
    for (int i = 0; i < getRoomSize(RoomType::Special); i++)
        floorRooms.specialRooms.push_back(getRoom(RoomType::Special, i).createRoomData());
    for (int i = 0; i < getRoomSize(RoomType::Normal); i++)
        floorRooms.standardsRooms.push_back(getRoom(RoomType::Normal, i).createRoomData());

    Vec2 bossRoomSize = getBossRoomSize();
    if (bossRoomSize.y * bossRoomSize.x >= getRoomSize(RoomType::Boss))
        return floorRooms;
    for (int i = 0; i < bossRoomSize.y; i++)
    {
        std::vector<RoomData> data;
        for (int j = 0; j < bossRoomSize.x; j++)
        {
            data.push_back(getRoom(RoomType::Boss, i * bossRoomSize.x + j).createRoomData());
        }


        floorRooms.bossRoom.push_back(data);
    }


    return floorRooms;
}

Floor::Floor(Rectangle pos)
{
    this->pos = pos;

    tree = new QuadTree({ pos.x - 100,pos.y - 100,pos.width + 200,pos.height + 200 });
    addObject(new Wall(pos.x - 100, pos.y - 100, 100, pos.height + 200));
    addObject(new Wall(pos.x - 100, pos.y - 100, pos.width + 200, 100));
    addObject(new Wall(pos.x + pos.width, pos.y - 100, 100, pos.height + 200));
    addObject(new Wall(pos.x - 100, pos.y + pos.height, pos.width + 200, 100));
    std::string path = "rooms.json";
    std::ifstream reader(path.c_str());
    if (reader.is_open())
    {
        nlohmann::json j;
        reader >> j;
        reader.close();
        loadRooms(j);
    }

    FloorRooms floorRooms = getFloorRooms();

    int floorW = pos.width / roomW;
    int floorH = pos.height / roomH;
    std::vector<std::vector<RoomData>> roomGrid = generareFloor(floorW, floorH, floorRooms);
    for (int i = 0; i < floorW; i++)
        for (int j = 0; j < floorH; j++)
        {
            int startX = roomW * i;
            int startY = roomH * j;
            int ID = roomGrid[j][i].ID;
            RoomType type = roomGrid[j][i].type;
            if (ID < 0)
                continue;
            Room room = getRoom(type,ID);

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