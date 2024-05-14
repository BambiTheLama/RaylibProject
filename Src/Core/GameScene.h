//
// Created by Szymek on 14.05.2024.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.h"
#include <vector>
#include "../GameObjects/GameObject.h"

class GameScene : public Scene{
    std::vector<GameObject*> gameObjects;
public:
    void start();

    void update(float deltaTime);

    void draw();
};



#endif //GAMESCENE_H
