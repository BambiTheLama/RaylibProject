#pragma once
#include "Scene.h"
#include <vector>
#include <list>
#include "../GameObjects/GameObject.h"
#include "../GameObjects/AddisionalTypes/CharacterController.h"

class Collider;

class GameScene : public Scene {
    std::list<GameObject *> gameObjects;
    std::list<Collider *> colliders;
    CharacterController *controller;

public:
    GameScene();

    ~GameScene();

    void start();

    void update(float deltaTime);

    void draw();

    std::list<GameObject *> getObjects() { return gameObjects; }

    bool addObject(GameObject *obj);
};
