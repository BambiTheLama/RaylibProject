#pragma once
#include "Scene.h"
#include <vector>
#include <list>
#include "../GameObjects/GameObject.h"
#include "../GameObjects/AddisionalTypes/CharacterController.h"
#include "QuadTree.h"
class Collider;

class GameScene : public Scene {
    std::list<GameObject *> gameObjects;
    std::list<GameObject*> toDelete;
    std::list<Collider *> colliders;
    std::list<Collider*> collidersToRemove;
    CharacterController controller;
    bool toSort = false;
    QuadTree* tree;
    Camera2D camera;
public:
    GameScene();

    ~GameScene();

    void start();

    void update(float deltaTime);

    void draw();

    std::list<GameObject*> getObjects(Rectangle pos) { return tree->getObjects(pos); }

    bool addObject(GameObject *obj);

    void deleteObject(GameObject* obj);
};

