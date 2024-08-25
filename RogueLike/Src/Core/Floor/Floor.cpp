#include "Floor.h"
#include "../WaveCollapsFun.h"
#include "Room.h"
#include "RoomElements.h"
#include <fstream>
#include "../../GameObjects/Characters/BossWall.h"
#include "../../GameObjects/Characters/LootBlock.h"
#include "../../GameObjects/Characters/SpawnPoint.h"
#include "../../GameObjects/Characters/StandardEnemy.h"
#include "raylib.hpp"
#include "raymath.h"
#include "../../GameObjects/AddisionalTypes/DrawUI.h"
#include "../../GameObjects/Game.h"

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
    const float wallSize = roomW * 5;
    tree = new QuadTree(RectangleIncreasSize(pos,wallSize));

    addObject(new BossWall(pos.x - wallSize, pos.y - wallSize, wallSize, pos.height + wallSize * 2));
    addObject(new BossWall(pos.x - wallSize, pos.y - wallSize, pos.width + wallSize * 2, wallSize));
    addObject(new BossWall(pos.x + pos.width, pos.y - wallSize, wallSize, pos.height + wallSize * 2));
    addObject(new BossWall(pos.x - wallSize, pos.y + pos.height, pos.width + wallSize * 2, wallSize));
    pathFinder = new PathFinder({ pos.width,pos.height }, { 13,13 });
    createFloor();
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
            if (rID == lrID && isWallType(type))
                sW++;
            else
            {
                if (lrID > 0)
                {
                    if (isWallType(type))
                        break;
                    if (type == BlockType::PlayerSpawnPoint)
                    {
                        GameObject* b = getRoomElement(lrID, startX + sX *tileW, startY + sY * tileH, tileW * sW, tileH * sH);
                        if (b)
                            addObject(b);
                        if (startPos.x <= 0 && startPos.y <= 0)
                            startPos = b->getPos();
                        else
                            endPos = b->getPos();
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
            //if (isWallType(type) && type != BlockType::BossEnterWall)
            //    pathFinder->setStaticBlock({ startX + sX * tileW, startY + sY * tileH, tileW * sW, tileH * sH });
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
    delete pathFinder;
    colliders.clear();
    for (auto o : toDelete)
    {
        removeObj(o);
        o->destroy();
    }
    for (auto o : toDelete)
        delete o;
    toDelete.clear();
    delete tree;
}

void Floor::createFloor()
{
    //std::string path = "Res/Rooms.json";
    //std::ifstream reader(path.c_str());
    //if (reader.is_open())
    //{
    //    nlohmann::json j;
    //    reader >> j;
    //    reader.close();
    //    loadRooms(j);
    //}

    loadRoomsFromPng("Res/Rooms/");



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

    setUpObjects(std::vector<int>{ 0,1,2 }, 5, BlockType::EnemySpawnPoint, roomGrid, getEnemy, 36, 36);
    setUpObjects(std::vector<int>{ -1 }, 50, BlockType::LootSpawnPoint, roomGrid, getObject, 36, 36);
    //setUpObjects(std::vector<int>{ 0 }, 1, BlockType::ElitEnemySpawn, roomGrid, getEnemy, 36, 36);
    setUpObjects(std::vector<int>{ 0 }, 10, BlockType::ChestSpawnPoint, roomGrid, getChest, 36, 36);
    removeCloseEnemies();
}

void Floor::start()
{
    for (auto o : allGameObjects)
    {
        o->start();
        Game::addObject(o);
    }

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
#ifdef ShowPaths
    static float reset = 0.0f;
    reset -= deltaTime;
    if (reset <= 0)
    {
        pathFinder->clearPaths();
        reset = 1.0f;
    }
#endif // ShowPath


    if (pathFinder)
        pathFinder->update();

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
        const float addRange = 600.0f;
        const float multiRange = 2.5f / camera.zoom;
        Vector2 offset = { camera.offset.x * multiRange + addRange,camera.offset.y * multiRange + addRange };

        camPos = Vector2Subtract(camPos, Vector2Scale(offset, 0.5f));

        Rectangle pos = { camPos.x,camPos.y,offset.x,offset.y };
        closeObjects.clear();
        closeObjects = tree->getObjects(pos);
    }
    colliders.clear();
    for (auto o : closeObjects)
    {
        if (o->getIsUpdate())
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
static bool pressedControl = false;
static bool pressedColliders = false;
static bool pressedQuadtree = false;
static bool pressedPathfinder = false;
void Floor::draw()
{
    for (auto o : closeObjects)
    {
        o->draw();
    }


    if (IsKeyPressed(KEY_LEFT_CONTROL))
    {
        pressedControl = !pressedControl;
        pressedColliders = false;
        pressedQuadtree = false;
        pressedPathfinder = false;
    }

    if(pressedControl)
    {
        if (IsKeyPressed(KEY_ONE))
            pressedColliders = !pressedColliders;
        if (pressedColliders)
            for (auto o : colliders)
                o->draw();
        if (IsKeyPressed(KEY_TWO))
            pressedQuadtree = !pressedQuadtree;
        if (pressedQuadtree)
            tree->draw();
#ifdef ShowPaths
        if (IsKeyPressed(KEY_THREE))
            pressedPathfinder = !pressedPathfinder;
        if (pressedPathfinder)
            pathFinder->draw();
#endif
    }

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
    std::string text = "DEBUG_MODE:\n";
    if (pressedColliders)
        text += "     -COLLIDES\n";
    if (pressedQuadtree)
        text += "     -QUADTREE\n";
    if (pressedPathfinder)
        text += "     -PATHFINDER\n";
    const char* ctext = text.c_str();
    const float textSize = 32;
    if (pressedControl)
        MyFont::DrawTextWithOutline(ctext, 0, GetScreenHeight() - MyFont::TextSize(ctext, textSize, 0).y, textSize, WHITE, BLACK);


}

std::list<GameObject*> Floor::getObjects(Rectangle pos) 
{
	return tree->getObjects(pos); 
}

bool Floor::addObject(GameObject* obj)
{
    if (!obj)
        return false;
    if (std::find(allGameObjects.begin(), allGameObjects.end(), obj) != allGameObjects.end())
    {
        tree->updatePos(obj);
        return true;
    }

    toRemove.remove(obj);
    
    allGameObjects.push_back(obj);
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
    {
        toDelete.push_back(obj);
        obj->destroy();
    }

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

void Floor::toCheckPos(Rectangle toCheck)
{
    if (pathFinder)
        pathFinder->addToCheck(toCheck);
}

bool Floor::canPassMap()
{
    if (!pathFinder)
        return true;
    return pathFinder->hasPath(startPos, endPos);
}

void Floor::setUpObjects(std::vector<int> objects, int numberOfObjects, BlockType type, std::vector<std::vector<RoomData>>& roomGrid, CreateObjectFun fun, int rangeW, int rangeH)
{
    if (objects.size() <= 0)
        return;
    Rectangle thisP = { 0,0,tileW * rangeW,tileH * rangeH };
    const float w = pos.width / thisP.width;
    const float h = pos.height / thisP.height;

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
            thisP.x = x * thisP.width;
            thisP.y = y * thisP.height;
            int elements = numberOfObjects;

            std::vector<Vector2> elementsPos;


            for (int i = 0; i < rangeW; i++)
                for (int j = 0; j < rangeH; j++)
                {
                    const int sx = x * rangeW + i;
                    const int sy = y * rangeH + j;
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
