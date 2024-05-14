//
// Created by Szymek on 14.05.2024.
//

#include "GameScene.h"
#include "../GameObjects/Player.h"

void GameScene::start() {
    Player *p = new Player(200, 200);
    gameObjects.push_back(p);
    controller = new CharacterController();
    controller->setCharacter(p);
}

void GameScene::update(float deltaTime) {
    for (auto o: gameObjects)
        o->update(deltaTime);
    controller->update(deltaTime);
}

void GameScene::draw() {
    for (auto o: gameObjects)
        o->draw();
}
