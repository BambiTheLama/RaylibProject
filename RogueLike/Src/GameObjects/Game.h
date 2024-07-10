#pragma once
#include <vector>
#include <list>
#include "GameObject.h"


class GameScene;

class Game {
    static GameScene *gameScene;

    Game() {}

public:
    static std::list<GameObject *> getObjects(Rectangle pos);

    static bool deleteObject(GameObject *obj);

    static void removeObject(GameObject* obj);

    static bool addObject(GameObject *obj);

    static bool isGameScene() { return gameScene; }

    friend class GameScene;
};

