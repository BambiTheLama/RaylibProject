//
// Created by Szymek on 16.05.2024.
//

#ifndef GAME_H
#define GAME_H
#include <vector>

#include "GameObject.h"


class GameScene;

class Game {
    static GameScene *gameScene;

    Game() {
    }

public:
    static GameObject *getObject(Rectangle pos);

    static std::vector<GameObject *> getObjects(Rectangle pos);

    static void deleteObject(GameObject *obj);

    static bool addObject(GameObject *obj);

    friend class GameScene;
};


#endif //GAME_H
