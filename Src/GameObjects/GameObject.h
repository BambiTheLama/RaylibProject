//
// Created by szymek on 14.05.2024.
//

#ifndef MYPROJECT_GAMEOBJECT_H
#define MYPROJECT_GAMEOBJECT_H
#include "raylib.h"

class GameObject {
protected:
    Rectangle pos;

public:
    virtual void update(float deltaTime) = 0;

    virtual void draw() = 0;

    Vector2 getPosPoint() { return {pos.x, pos.y}; }

    Rectangle getPos() { return pos; }
};


#endif //MYPROJECT_GAMEOBJECT_H
