#pragma once
#include "raylib.h"
#include "../../Core/Controller.h"

class Character {
public:
    virtual void move(Vector2 dir, float deltaTime) = 0;

    virtual void action(Input input) = 0;
};

