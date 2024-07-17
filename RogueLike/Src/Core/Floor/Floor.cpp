#include "Floor.h"
#include "../WaveCollapsFun.h"
#include "Room.h"
#include "RoomElements.h"
#include <fstream>
#include "../../GameObjects/Characters/BossWall.h"
#include "../../GameObjects/Characters/LootBlock.h"
#include "../../GameObjects/Characters/SpawnPoint.h"
#include "../../GameObjects/Characters/Wolf.h"
#include "raylib.hpp"
#include "raymath.h"
#include "../../GameObjects/AddisionalTypes/DrawUI.h"

FloorRooms getFloorRooms()
{
    FloorRooms floorRooms;
    for (int i = 0; i < getRoomSize(RoomType::Special); i++)
        floorRooms.specialRooms.push_back(getRoom(RoomType::Special, i).createRoomData());
    for (int i = 0; i < getRoomSize(RoomType::Normal); i++)
        floorRooms.standardsRooms.push_back(getRoom(RoomType::Normal, i).createRoomData());

    Vec2 bossRoomSize = getBossRoomSize();
    if (bossRoomSize.y * bossRoomSize.x > getRoomSize(RoomType::Boss))
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
    pos.width = (float)(((int)pos.width / (int)roomW) * (int)roomW);
    pos.height = (float)(((int)pos.height / (int)roomH) * (int)roomH);
    this->pos = pos;
    tree = new QuadTree({ pos.x - 100.0f,pos.y - 100.0f,pos.width + 200.0f,pos.height + 200.0f });
}

void Floor::setUpRooms(int startX, int startY, Room& room)
{
    int roomID[roomSize][roomSize];
    for (int x = 0; x < roomSize; x++)
        for (int y = 0; y < roomSize; y++)
            roomID[y][x] = room.getBlockID(x, y);

    int lrID = -1;
    int rID = -1;
    int sX = -1;
    int sY = -1;
    int sW = -1;
    int sH = -1;
    for (int y = 0; y < roomSize; y++)
    {
        sX = -1;
        sY = -1;
        lrID = -1;
        sH = 1;
        sW = 1;
        BlockType type = getRoomElementType(rID);
        for (int x = 0; x < roomSize; x++)
        {
            rID = roomID[y][x];
            if (rID == lrID && (type == BlockType::Wall || type == BlockType::BossEnterWall))
                sW++;
            else
            {
                if (lrID > 0)
                {
                    if (type == BlockType::Wall || type == BlockType::BossEnterWall)
                        break;
                    if (type == BlockType::PlayerSpawnPoint)
                    {
                        GameObject* b = getRoomElement(lrID, startX + sX *tileW, startY + sY * tileH, tileW * sW, tileH * sH);
                        if (b)
                            addObject(b);
                    }

                }

                sX = x;
                sY = y;
                sH = 1;
                sW = 1;
                lrID = rID;
                type = getRoomElementType(rID);
            }
            if (rID <= 0)
                continue;
            roomID[y][x] = 0;
        }
        if (lrID > 0 && sH > 0 && sW > 0)
        {
            bool isbreak = false;
            int k = 1;
            do {

                for (int x = sX; x < sX + sW; x++)
                {
                    if (roomID[k + y][x] != lrID)
                    {
                        isbreak = true;
                        break;
                    }
                }
                if (!isbreak)
                {
                    sH++;
                    for (int x = sX; x < sX + sW; x++)
                    {
                        roomID[k + y][x] = 0;

                    }
                }
                k++;
            } while (!isbreak && k + y < roomSize);
            GameObject* b = getRoomElement(lrID, startX + sX * tileW, startY + sY * tileH, tileW * sW, tileH * sH);
            if (b)
                addObject(b);
            y--;
        }

    }
}

Floor::~Floor()
{
    for (auto o : allGameObjects)
    {
        deleteObject(o);
    }

    colliders.clear();
    for (auto o : toDelete)
    {
        removeObj(o);
        delete o;
    }

    toDelete.clear();
    delete tree;
}


void Floor::createFloor()
{

    addObject(new BossWall(pos.x - 100.0f, pos.y - 100.0f, 100.0f, pos.height + 200.0f));
    addObject(new BossWall(pos.x - 100.0f, pos.y - 100.0f, pos.width + 200.0f, 100.0f));
    addObject(new BossWall(pos.x + pos.width, pos.y - 100.0f, 100.0f, pos.height + 200.0f));
    addObject(new BossWall(pos.x - 100.0f, pos.y + pos.height, pos.width + 200.0f, 100.0f));


    FloorRooms floorRooms = getFloorRooms();

    int floorW = (int)(pos.width / roomW);
    int floorH = (int)(pos.height / roomH);
    std::vector<std::vector<RoomData>> roomGrid = generareFloor(floorW, floorH, floorRooms);
    for (int i = 0; i < floorW; i++)
        for (int j = 0; j < floorH; j++)
        {
            int startX = (int)roomW * i;
            int startY = (int)roomH * j;
            int ID = roomGrid[j][i].ID;
            RoomType type = roomGrid[j][i].type;
            if (ID < 0)
                continue;
            Room room = getRoom(type, ID);
            setUpRooms(startX, startY, room);
        }

    setUpObjects(std::vector<int>{ 0 }, 5, BlockType::EnemySpawnPoint, roomGrid, getEnemy);
    setUpObjects(std::vector<int>{ 0 }, 40, BlockType::LootSpawnPoint, roomGrid, getObject);
    setUpObjects(std::vector<int>{ 0 }, 1, BlockType::ElitEnemySpawn, roomGrid, getEnemy);
    removeCloseEnemies();
}

void Floor::start()
{
    createFloor();
    for (auto o : allGameObjects)
        o->start();
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

void Floor::update(float deltaTime,Camera2D camera)
{
    for (auto o : toRemove)
    {
        removeObj(o);
    }
    toRemove.clear();
    for (auto o : toDelete)
    {
        removeObj(o);
        o->destroy();
        delete o;
    }
    toDelete.clear();
    //std::list<GameObject*> gameObjects;
    if (!tree)
        closeObjects = allGameObjects;
    else
    {
        Vector2 camPos = camera.target;
        Vector2 offset = { camera.offset.x * 2.2f / camera.zoom + 300.0f,camera.offset.y * 2.2f / camera.zoom + 300.0f };

        camPos = Vector2Subtract(camPos, Vector2Scale(offset, 0.5f));

        Rectangle pos = { camPos.x,camPos.y,offset.x,offset.y };
        closeObjects.clear();
        closeObjects = tree->getObjects(pos);
    }
    colliders.clear();
    for (auto o : closeObjects)
    {
        o->update(deltaTime);
        if(o->movingObject())
            tree->updatePos(o);
        Collider* col = dynamic_cast<Collider*>(o);
        if (col)
            colliders.push_back(col);
    }
    for (auto o : colliders)
        o->update(deltaTime);
    for (auto o : colliders)
        o->clearCollider();
    for (auto o : colliders)
        o->checkCollision(deltaTime);

    closeObjects.sort(sortGameObjectCondiction);
}

void Floor::draw()
{
    for (auto o : closeObjects)
    {
        o->draw();
    }

    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_ONE))
        for (auto o : colliders) {
            o->draw();
        }


    if (IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyDown(KEY_TWO))
        tree->draw();
}

void Floor::drawUI()
{
    MyFont::DrawTextWithOutline(TextFormat("%d/%d", closeObjects.size(), allGameObjects.size()), 0, 64, 32, WHITE, BLACK);
    for (auto o : closeObjects)
    {
        DrawUI* ui = dynamic_cast<DrawUI*>(o);
        if (ui)
            ui->drawUI();
    }

}

std::list<GameObject*> Floor::getObjects(Rectangle pos) 
{
	return tree->getObjects(pos); 
}

bool Floor::addObject(GameObject* obj)
{
    if (!obj)
        return false;
    auto find = std::find(allGameObjects.begin(), allGameObjects.end(), obj);
    if (find != allGameObjects.end())
    {
        tree->updatePos(obj);
        return true;
    }
    allGameObjects.push_back(obj);
    Collider* collider = dynamic_cast<Collider*>(obj);
    if (collider)
    {
        if (!collider->solidObject)
            colliders.push_back(collider);

    }
    tree->addObj(obj);
    obj->start();
    return true;
}

bool Floor::deleteObject(GameObject* obj)
{
    if (!obj)
        return true;
    if (std::find(allGameObjects.begin(), allGameObjects.end(), obj) == allGameObjects.end())
        return false;
    if (std::find(toDelete.begin(), toDelete.end(), obj) == toDelete.end())
        toDelete.push_back(obj);
    return true;
}

void Floor::removeObject(GameObject* obj)
{
    if (!obj)
        return;
    if (std::find(toDelete.begin(), toDelete.end(), obj) != toDelete.end())
        return;
    if (std::find(toRemove.begin(), toRemove.end(), obj) == toRemove.end())
        toRemove.push_back(obj);
}

void Floor::setUpObjects(std::vector<int> objects, int numberOfObjects, BlockType type, std::vector<std::vector<RoomData>>& roomGrid, CreateObjectFun fun)
{
    if (objects.size() <= 0)
        return;
    const int sw = 50;
    const int sh = 50;
    Rectangle thisP = { 0,0,tileW * sw,tileH * sh };
    const float w = pos.width / thisP.width;
    const float h = pos.height / thisP.height;

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
            thisP.x = x * thisP.width;
            thisP.y = y * thisP.height;
            int elements = numberOfObjects;

            std::vector<Vector2> elementsPos;


            for (int i = 0; i < sw; i++)
                for (int j = 0; j < sh; j++)
                {
                    const int sx = x * sw + i;
                    const int sy = y * sh + j;
                    const int gx = sx / roomSize;
                    const int gy = sy / roomSize;
                    const int rx = sx % roomSize;
                    const int ry = sy % roomSize;
                    if (roomGrid.size() <= gy || roomGrid[0].size() <= gx)
                        continue;
                    int ID = roomGrid[gy][gx].ID;
                    RoomType rType = roomGrid[gy][gx].type;
                    Room r = getRoom(rType, ID);
                    int bID = r.getBlockID(rx, ry);
                    if (getRoomElementType(bID) == type)
                        elementsPos.push_back({ (float)sx * tileW,(float)sy * tileH });
                }

            if (elementsPos.size() <= elements)
            {
                for (auto o : elementsPos)
                {
                    int ID = objects[rand() % objects.size()];
                    Rectangle pos = { o.x,o.y,tileW,tileH };
                    addObject(fun(ID, pos));
                }
            }
            else
            {
                for (; elements > 0 && elementsPos.size() > 0; elements--)
                {
                    int e = rand() % elementsPos.size();
                    Vector2 vPos = elementsPos[e];
                    Rectangle pos = { vPos.x,vPos.y,tileW,tileH };
                    int ID = objects[rand() % objects.size()];
                    addObject(fun(ID, pos));
                    elementsPos.erase(elementsPos.begin() + e);
                }
            }
        }
}

void Floor::removeCloseEnemies()
{
    Rectangle rPos;
    rPos.width = 1600;
    rPos.height = 1600;
    rPos.x = pos.x + pos.width / 2 - rPos.width / 2;
    rPos.y = pos.y + pos.height / 2 - rPos.height / 2;

    std::list<GameObject*> gm = tree->getObjects(rPos);
    for (auto o : gm)
    {
        if (o->getType() != ObjectType::Enemy)
            continue;
        deleteObject(o);

    }
}
void Floor::removeObj(GameObject* o)
{
    tree->removeObj(o);
    allGameObjects.remove(o);
    Collider* collider = dynamic_cast<Collider*>(o);
    if (!collider)
        return;

    colliders.remove(collider);
    for (auto c : colliders)
        c->removeObject(collider);
    
}