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

std::vector<GameObject *> Game::getObjects(Rectangle pos) {
    if (!gameScene)
        return std::vector<GameObject *>();
}

bool Game::addObject(GameObject *obj) {
    if (!gameScene)
        return false;
    return true;
}

void Game::deleteObject(GameObject *obj) {
    if (!gameScene)
        return;
}


