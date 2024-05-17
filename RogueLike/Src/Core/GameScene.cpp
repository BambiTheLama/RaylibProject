#include "GameScene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Game.h"
#include <algorithm>
#include "../GameObjects/Wall.h"

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
    controller = new CharacterController();
    controller->setCharacter(p);
    gameObjects.push_back(new Player(500, 200));
    for (auto o: gameObjects) {
        Collider *col = dynamic_cast<Collider *>(o);
        if (col)
            colliders.push_back(col);
    }
}

void GameScene::update(float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 cursor = GetMousePosition();
        addObject(new Wall(cursor.x, cursor.y));
    }

    for (auto o: gameObjects)
        o->update(deltaTime);
    controller->update(deltaTime);
    for (auto o: colliders) {
        o->clearCollider();
    }
    for (auto o: colliders)
        o->checkCollision();
}

bool GameScene::addObject(GameObject *obj) {
    auto find = std::find(gameObjects.begin(), gameObjects.end(), obj);
    if (find != gameObjects.end())
        return true;
    gameObjects.push_back(obj);
    Collider *collider = dynamic_cast<Collider *>(obj);
    if (collider)
        colliders.push_back(collider);
    return true;
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
