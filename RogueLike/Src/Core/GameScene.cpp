#include "GameScene.h"
#include "../GameObjects/Characters/Player.h"
#include "../GameObjects/Game.h"
#include <algorithm>
#include "../GameObjects/Characters/Wall.h"
#include "../GameObjects/Characters/Wolf.h"
#include "../GameObjects/Characters/SpawnPoint.h"
#include "Controller/Controller.h"
#include "rlgl.h"
#include "WaveCollapsFun.h"
#include "../GameObjects/Weapon/Weapon.h"

GameScene::GameScene() {
    Game::gameScene = this;
    Weapon::loadWeaponData("Res/Weapon.json");
    camera.zoom = 1.01f;
    camera.rotation = 0;
    camera.offset = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    Rectangle pos = { 0,0,6000,6000 };
    floor = new Floor(pos);
    camera.target = { pos.width / 2,pos.height / 2 };

    std::list<GameObject*>objs = floor->getObjects({ pos.x + pos.width / 2 - 100,pos.y + pos.height / 2 - 100,200,200 });
    float sx = pos.width / 2, sy = pos.height / 2;
    for (auto o : objs)
    {
        if (o->getType() != ObjectType::SpawnPoint)
            continue;
        SpawnPoint* sp = dynamic_cast<SpawnPoint*>(o);
        if (!sp)
            continue;
        if (sp->getType() != BlockType::PlayerSpawnPoint)
            continue;
        Rectangle sPos = sp->getPos();
        sx = sPos.x + sPos.width / 2;
        sy = sPos.y + sPos.height / 2;
        deleteObject(o);
        break;
    }
    controller.setCharacterType(ObjectType::Player);
    Player* gm = new Player(sx, sy);
    if (gm)
    {
        addObject(gm);
        controller.setCharacter(gm);
    }
}

GameScene::~GameScene() {

    Game::gameScene = nullptr;
    Floor* f = floor;
    floor = nullptr;
    delete f;
}


void GameScene::start() {

    Game::gameScene = this;
    floor->start();

}

void GameScene::onDestroy()
{

}

void GameScene::update(float deltaTime) {
    Vector2 cursor = GetScreenToWorld2D(GetMousePosition(), camera);
    if (IsKeyDown(KEY_UP))
        camera.zoom += deltaTime;
    if (IsKeyDown(KEY_DOWN))
        camera.zoom -= deltaTime;
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        for (int i = 0; i < 1; i++)
            addObject(new Wolf(cursor.x + i, cursor.y + i));
    }

    if (false && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::list<GameObject*> objects = getObjects({ cursor.x - 1,cursor.y - 1,3,3 });
        for(auto o:objects)
            if (CheckCollisionPointRec(cursor, o->getPos()))
            {
                Character* ch = dynamic_cast<Character*>(o);
                if(ch)
                    ch->destoryController();
                if (ch && ch->canBeControllerd(&controller))
                    controller.setCharacter(ch);
            }
    }
    if (floor)
        floor->update(deltaTime,camera);
    controller.update(deltaTime);

    if(controller.hasCharacter())
        camera.target = controller.getPos();
}

std::list<GameObject*> GameScene::getObjects(Rectangle pos)
{
    if(floor)
        return floor->getObjects(pos); 
    return std::list<GameObject*>();
}

Rectangle GameScene::convertFromWorldToScrean(Rectangle pos)
{
    Vector2 v = GetWorldToScreen2D({ pos.x,pos.y }, camera);
    pos.x = v.x;
    pos.y = v.y;
    pos.width *= camera.zoom;
    pos.height *= camera.zoom;
    return pos;
}

bool GameScene::addObject(GameObject *obj) {
    if (floor)
        return floor->addObject(obj);
    return false;
}
bool GameScene::deleteObject(GameObject* obj)
{
    if (floor)
        return floor->deleteObject(obj);
    return false;
}

void GameScene::removeObject(GameObject* obj)
{
    if (floor)
        floor->removeObject(obj);
}

void GameScene::draw() {
    BeginMode2D(camera);
    if (floor)
        floor->draw();
    EndMode2D();
    if (floor)
        floor->drawUI();
}
