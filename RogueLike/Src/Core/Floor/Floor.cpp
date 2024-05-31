#include "Floor.h"
#include "../WaveCollapsFun.h"
#include "Room.h"
#include "RoomElements.h"
#include <fstream>
#include "../../GameObjects/Characters/BossWall.h"
#include "../../GameObjects/Characters/LootBlock.h"
#include "../../GameObjects/Characters/SpawnPoint.h"
#include "../../GameObjects/Characters/Wolf.h"

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
    pos.width = ((int)pos.width / (int)roomW) * (int)roomW;
    pos.height = ((int)pos.height / (int)roomH) * (int)roomH;
    this->pos = pos;

    tree = new QuadTree({ pos.x - 100,pos.y - 100,pos.width + 200,pos.height + 200 });
    addObject(new BossWall(pos.x - 100, pos.y - 100, 100, pos.height + 200));
    addObject(new BossWall(pos.x - 100, pos.y - 100, pos.width + 200, 100));
    addObject(new BossWall(pos.x + pos.width, pos.y - 100, 100, pos.height + 200));
    addObject(new BossWall(pos.x - 100, pos.y + pos.height, pos.width + 200, 100));


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
            setUpRooms(startX, startY, room);
        }
    setUpObjects(std::vector<int>{ 0 }, 1, BlockType::EnemySpawnPoint);
    setUpObjects(std::vector<int>{ 1 }, 20, BlockType::LootSpawnPoint);
    setUpObjects(std::vector<int>{ -1 }, 1, BlockType::ElitEnemySpawn);
    removeCloseEnemies();
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
                    GameObject* b = getRoomElement(lrID, startX + sX * tileW, startY + sY * tileH, tileW * sW, tileH * sH);
                    if (b)
                        addObject(b);
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
        deleteObject(o);
    colliders.clear();
    for (auto o : toDelete)
    {
        allGameObjects.remove(o);
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

void Floor::start()
{
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
    for (auto o : toDelete)
    {
        tree->removeObj(o);
        allGameObjects.remove(o);
        Collider* collider = dynamic_cast<Collider*>(o);
        if (collider) {
            colliders.remove(collider);
            for (auto c : colliders)
                c->removeObject(collider);
        }
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
        Vector2 offset = { camera.offset.x * 1.0f / camera.zoom,camera.offset.y * 1.5f * 1.0f / camera.zoom };
        offset.x += 250;
        offset.y += 250;
        camPos.x -= offset.x;
        camPos.y -= offset.y;
        offset.x *= 2;
        offset.y *= 2;
        Rectangle pos = { camPos.x,camPos.y,offset.x,offset.y };
        closeObjects = tree->getObjects(pos);
    }
    for (auto o : closeObjects)
    {
        o->update(deltaTime);
        if(o->movingObject())
            tree->updatePos(o);
    }

    //tree->update();

    for (auto o : colliders)
        o->clearCollider();
    for (auto o : colliders)
        o->checkCollision(deltaTime);
    for (auto c : collidersToRemove)
        colliders.remove(c);
    collidersToRemove.clear();
    closeObjects.sort(sortGameObjectCondiction);
}

void Floor::draw()
{
    for (auto o : closeObjects)
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

void Floor::drawUI()
{
    MyFont::DrawTextWithOutline(TextFormat("%d/%d", closeObjects.size(), allGameObjects.size()), 0, 64, 32, WHITE, BLACK);
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
        return true;
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

void Floor::setUpObjects(std::vector<int> objects, int numberOfObjects, BlockType type)
{
    if (objects.size() <= 0)
        return;
    Rectangle thisP = { 0,0,1600,900 };
    float w = pos.width / thisP.width;
    float h = pos.height / thisP.height;

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
            thisP.x = x * thisP.width;
            thisP.y = y * thisP.height;
            int elements = numberOfObjects;
            std::list<GameObject*> gm = tree->getObjects(thisP);
            std::vector<SpawnPoint*> spawnPoints;
            for (auto o : gm)
            {
                if (o->getType() != ObjectType::SpawnPoint)
                    continue;
                SpawnPoint* sp = dynamic_cast<SpawnPoint*>(o);
                if (!sp)
                    continue;
                if (sp->getType() != type)
                    continue;
                spawnPoints.push_back(sp);
            }
            for (auto o : spawnPoints)
                deleteObject(o);
            if (spawnPoints.size() <= elements)
            {
                for (auto o : spawnPoints)
                {
                    int ID = objects[rand() % objects.size()];
                    addObject(getObject(ID, o->getPos()));
                }
            }
            else
            {
                for (; elements > 0 && spawnPoints.size() > 0; elements--)
                {
                    int e = rand() % spawnPoints.size();
                    Rectangle pos = spawnPoints[e]->getPos();
                    int ID = objects[rand() % objects.size()];
                    addObject(getObject(ID, pos));
                    spawnPoints.erase(spawnPoints.begin() + e);

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
