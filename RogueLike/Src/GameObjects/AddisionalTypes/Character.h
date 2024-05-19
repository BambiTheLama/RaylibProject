#pragma once
#include "raylib.h"
#include "../../Core/Controller.h"


class CharacterController;

class Character {
    CharacterController* controllBy = nullptr;
public:
    virtual void move(Vector2 dir, float deltaTime) = 0;

    virtual void action(Input input) = 0;

    bool canBeControllerd(CharacterController* c) { return !controllBy || c == controllBy; }

    void setController(CharacterController* c)
    {
        if (!controllBy || c == controllBy)
            controllBy = c;
    }
};

