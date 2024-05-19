#include "GameScene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Game.h"
#include <algorithm>
#include "../GameObjects/Wall.h"
#include "../GameObjects/Enemy.h"

GameScene::GameScene() {
    Game::gameScene = this;
}

GameScene::~GameScene() {
    Game::gameScene = nullptr;
    for (auto o: gameObjects)
        delete o;
    
    gameObjects.clear();
}


void GameScene::start() {
    Player *p = new Player(200, 200);
    gameObjects.push_back(p);
    controller.setCharacter(p);
    gameObjects.push_back(new Player(500, 200));
    for (auto o: gameObjects) {
        Collider *col = dynamic_cast<Collider *>(o);
        if (col)
            colliders.push_back(col);
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

void GameScene::update(float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 cursor = GetMousePosition();

        addObject(new Wall(cursor.x, cursor.y));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        Vector2 cursor = GetMousePosition();

        addObject(new Enemy(cursor.x, cursor.y));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 cursor = GetMousePosition();
        std::list<GameObject*> objects=getObjects();
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
    controller.update(deltaTime);

    for (auto o : colliders)
        o->clearCollider();
    for (auto o: colliders)
        o->checkCollision();


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
    return true;
}
void GameScene::deleteObject(GameObject* obj)
{
    gameObjects.remove(obj);
    Collider* collider = dynamic_cast<Collider*>(obj);
    if (collider) {
        colliders.remove(collider);
    }

    toDelete.push_back(obj);
}

void GameScene::draw() {
    for (auto o: gameObjects)
        o->draw();
#ifdef showColliders
    for (auto o: colliders) {
        o->draw();
    }
#endif
}
