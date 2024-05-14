//
// Created by szymek on 14.05.2024.
//

#ifndef MYPROJECT_PLAYER_H
#define MYPROJECT_PLAYER_H
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(int x = 0, int y = 0);

    void update(float deltaTime);

    void draw();
};


#endif //MYPROJECT_PLAYER_H
