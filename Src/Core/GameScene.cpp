//
// Created by Szymek on 14.05.2024.
//

#include "GameScene.h"
#include "../GameObjects/Player.h"

void GameScene::start() {
    gameObjects.push_back(new Player);
}

void GameScene::update(float deltaTime) {
    for (auto o: gameObjects)
        o->update(deltaTime);
}

void GameScene::draw() {
    for (auto o: gameObjects)
        o->draw();
}
