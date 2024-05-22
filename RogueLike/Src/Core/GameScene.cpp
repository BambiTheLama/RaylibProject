#include "GameScene.h"
#include "../GameObjects/Characters/Player.h"
#include "../GameObjects/Game.h"
#include <algorithm>
#include "../GameObjects/Characters/Wall.h"
#include "../GameObjects/Characters/Wolf.h"

GameScene::GameScene() {
    Game::gameScene = this;
    tree = new QuadTree({ -3000,-3000,6000,6000 });
    camera.zoom = 1;
    camera.rotation = 0;
    camera.offset = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
}

GameScene::~GameScene() {
    Game::gameScene = nullptr;
    for (auto o: gameObjects)
        delete o;
    gameObjects.clear();
    delete tree;

}


void GameScene::start() {
    addObject(new Player(200, 200));
    //controller.setCharacter(p);
    controller.setCharacterType(ObjectType::Player);
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
    Vector2 cursor = GetScreenToWorld2D(GetMousePosition(), camera);
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        addObject(new Wall(cursor.x, cursor.y));
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
                ch->destoryController();
                if (ch && ch->canBeControllerd(&controller))
                    controller.setCharacter(ch);
            }
    }
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
    camera.target = controller.getPos();
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
    BeginMode2D(camera);
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
    EndMode2D();
}
