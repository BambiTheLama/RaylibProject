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

    void toCheckPos(Rectangle toCheck);

    std::list<GameObject*> getObjects(Rectangle pos);

    Rectangle convertFromWorldToScrean(Rectangle pos);

    Vector2 getDirToGo(Rectangle start, Rectangle end, float range);

    bool addObject(GameObject *obj);

    bool deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);
};

