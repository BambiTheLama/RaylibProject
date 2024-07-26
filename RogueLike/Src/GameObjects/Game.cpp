#include "Game.h"
#include "../Core/GameScene.h"

GameScene *Game::gameScene = nullptr;

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

bool Game::deleteObject(GameObject *obj) {
    if (!obj)
        return true;
    if (!gameScene)
        return false;
    return gameScene->deleteObject(obj);
}

Rectangle Game::convertFromWorldToScrean(Rectangle pos)
{
    if (!gameScene)
        return pos;
    return gameScene->convertFromWorldToScrean(pos);
}

Vector2 Game::getDirToGo(Rectangle start, Rectangle end, float range)
{
    if (!gameScene)
        return { 0,0 };
    return gameScene->getDirToGo(start, end, range);
}
void Game::toCheckPos(Rectangle toCheck)
{
    if (!gameScene)
        return;
    gameScene->toCheckPos(toCheck);
}

void Game::removeObject(GameObject* obj)
{
    if (!obj)
        return;
    if (!gameScene)
        return;
    gameScene->removeObject(obj);
}