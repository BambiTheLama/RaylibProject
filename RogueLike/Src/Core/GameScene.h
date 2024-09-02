#pragma once
#include "Scene.h"
#include <vector>
#include <list>
#include "Floor/Floor.h"
#include "QuadTree.h"
#include "../GameObjects/AddisionalTypes/CharacterController.h"

class GameScene : public Scene {
    CharacterController controller;
    RenderTexture2D sceneFrame;
    RenderTexture2D shadowsFrame;
    RenderTexture2D lightFrame;
    Floor* floor = nullptr;
    Camera2D camera;
    Color shadowColor = BLACK;//{ 25,25,25,255 };
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

    std::list<Vector3> getPathToGo(Rectangle start, Rectangle end, float range);

    bool isObjectAtScene(GameObject* gm);

    bool addObject(GameObject *obj);

    bool deleteObject(GameObject* obj);

    void removeObject(GameObject* obj);

    void onResize();
};

