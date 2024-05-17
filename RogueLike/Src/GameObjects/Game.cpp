//
// Created by Szymek on 16.05.2024.
//
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
    return gameScene->getObjects();
}

bool Game::addObject(GameObject *obj) {
    if (!gameScene)
        return false;
    return gameScene->addObject(obj);
}

void Game::deleteObject(GameObject *obj) {
    if (!gameScene)
        return;
}


