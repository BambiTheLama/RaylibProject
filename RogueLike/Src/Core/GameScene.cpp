#include "GameScene.h"
#include "../GameObjects/Characters/Player.h"
#include "../GameObjects/Game.h"
#include <algorithm>
#include "../GameObjects/Characters/Wall.h"
#include "../GameObjects/Characters/Wolf.h"
#include "Controller.h"


GameScene::GameScene() {
    Game::gameScene = this;
    camera.zoom = 1;
    camera.rotation = 0;
    camera.offset = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
    floor = new Floor({ 0,0,3000,3000 });
}

GameScene::~GameScene() {
    Game::gameScene = nullptr;
    delete floor;
}


void GameScene::start() {
    Game::gameScene = this;
    addObject(new Player(200, 200));
    controller.setCharacterType(ObjectType::Player);
}

void GameScene::update(float deltaTime) {
    Vector2 cursor = GetScreenToWorld2D(GetMousePosition(), camera);
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        for(int i=0;i<10;i++)
        addObject(new Wall(cursor.x+i, cursor.y+i));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        for (int i = 0; i < 1; i++)
            addObject(new Wolf(cursor.x + i, cursor.y + i));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
        floor->update(deltaTime);
    controller.update(deltaTime);
    camera.target = controller.getPos();
}

std::list<GameObject*> GameScene::getObjects(Rectangle pos)
{
    if(floor)
        return floor->getObjects(pos); 
    return std::list<GameObject*>();
}
bool GameScene::addObject(GameObject *obj) {

    if (floor)
        return floor->addObject(obj);
    return false;
}
void GameScene::deleteObject(GameObject* obj)
{
    if (floor)
        floor->deleteObject(obj);
}

void GameScene::draw() {
    BeginMode2D(camera);
    if (floor)
        floor->draw();
    EndMode2D();
}
