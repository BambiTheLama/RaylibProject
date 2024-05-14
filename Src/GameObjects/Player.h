//
// Created by szymek on 14.05.2024.
//

#ifndef MYPROJECT_PLAYER_H
#define MYPROJECT_PLAYER_H
#include "GameObject.h"
#include "AddisionalTypes/Character.h"


class Player : public GameObject, public Character {
    float speed = 100;

public:
    Player(int x = 0, int y = 0);

    void update(float deltaTime);

    void move(Vector2 dir, float deltaTime);

    void action(Input input);

    void draw();
};


#endif //MYPROJECT_PLAYER_H
