#pragma once
#include "Scene.h"
#include <vector>
#include <list>
#include "Floor/Floor.h"
#include "QuadTree.h"
#include "../GameObjects/AddisionalTypes/CharacterController.h"

class GameScene : public Scene {
    CharacterController controller;
    Floor* floor = nullptr;
    Camera2D camera;
public:
    GameScene();

    ~GameScene();

    void start();

    void onDestroy();

    void update(float deltaTime);

    void draw();

    std::list<GameObject*> getObjects(Rectangle pos);

    bool addObject(GameObject *obj);

    bool deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);
};

