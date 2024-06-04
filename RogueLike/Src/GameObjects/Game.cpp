#include "Game.h"
#include "../Core/GameScene.h"

GameScene *Game::gameScene = nullptr;

GameObject *Game::getObject(Rectangle pos) {
    if (!gameScene)
        return nullptr;
}

std::list<GameObject *> Game::getObjects(Rectangle pos) {
    if (!gameScene)
        return std::list<GameObject *>();
    return gameScene->getObjects(pos);
}

bool Game::addObject(GameObject *obj) {
    if (!obj)
        return false;
    if (!gameScene)
        return false;
    return gameScene->addObject(obj);
}

void Game::deleteObject(GameObject *obj) {
    if (!obj)
        return;
    if (!gameScene)
        return;
    gameScene->deleteObject(obj);
}


void Game::removeObject(GameObject* obj)
{
    if (!obj)
        return;
    if (!gameScene)
        return;
    gameScene->removeObject(obj);
}