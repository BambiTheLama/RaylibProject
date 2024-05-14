//
// Created by Szymek on 14.05.2024.
//

#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "../../Core/Controller.h"

class Character {
public:
    virtual void move(Vector2 dir, float deltaTime) = 0;

    virtual void action(Input input) = 0;
};

#endif //CHARACTER_H
