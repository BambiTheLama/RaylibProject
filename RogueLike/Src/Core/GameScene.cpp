#include "GameScene.h"
#include "../GameObjects/Characters/Player.h"
#include "../GameObjects/Game.h"
#include <algorithm>
#include "../GameObjects/Characters/Wall.h"
#include "../GameObjects/Characters/Wolf.h"

GameScene::GameScene() {
    Game::gameScene = this;
    tree = new QuadTree({ -3000,-3000,6000,6000 });
}

GameScene::~GameScene() {
    Game::gameScene = nullptr;
    for (auto o: gameObjects)
        delete o;
    
    gameObjects.clear();
}


void GameScene::start() {
    Player *p = new Player(200, 200);
    addObject(p);
    controller.setCharacter(p);
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

void GameScene::update(float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 cursor = GetMousePosition();

        addObject(new Wall(cursor.x, cursor.y));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        Vector2 cursor = GetMousePosition();
        for (int i = 0; i < 10; i++)
            addObject(new Wolf(cursor.x + i, cursor.y + i));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 cursor = GetMousePosition();
        std::list<GameObject*> objects = getObjects({ cursor.x - 1,cursor.y - 1,3,3 });
        for(auto o:objects)
            if (CheckCollisionPointRec(cursor, o->getPos()))
            {
                Character* ch = dynamic_cast<Character*>(o);
                if (ch && ch->canBeControllerd(&controller))
                    controller.setCharacter(ch);
            }
    }
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
    for (auto o: gameObjects)
        o->update(deltaTime);
    tree->update();
    controller.update(deltaTime);

    for (auto o : colliders)
        o->clearCollider();
    for (auto o: colliders)
        o->checkCollision();
    for (auto c : collidersToRemove)
        colliders.remove(c);
    collidersToRemove.clear();

    gameObjects.sort(sortGameObjectCondiction);
}

bool GameScene::addObject(GameObject *obj) {

    auto find = std::find(gameObjects.begin(), gameObjects.end(), obj);
    if (find != gameObjects.end())
        return true;
    gameObjects.push_back(obj);
    toSort = true;
    Collider *collider = dynamic_cast<Collider *>(obj);
    if (collider)
        colliders.push_back(collider);
    tree->addObj(obj);
    return true;
}
void GameScene::deleteObject(GameObject* obj)
{
    Collider* collider = dynamic_cast<Collider*>(obj);
    if (collider) {
        collidersToRemove.remove(collider);
    }
    tree->removeObj(obj);
    toDelete.push_back(obj);
}

void GameScene::draw() {

    for (auto o : gameObjects)
    {
        o->draw();
    }

#ifdef showColliders
    for (auto o: colliders) {
        o->draw();
    }
#endif
    if(IsKeyDown(KEY_TAB))
        tree->draw();
}
