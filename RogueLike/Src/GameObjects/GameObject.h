#pragma once
#include "raylib.h"

class GameObject {
protected:
    Rectangle pos;

public:
    virtual ~GameObject() {
    }

    virtual void update(float deltaTime) = 0;

    virtual void draw() = 0;

    Vector2 getPosPoint() { return {pos.x, pos.y}; }

    Rectangle getPos() { return pos; }
};

