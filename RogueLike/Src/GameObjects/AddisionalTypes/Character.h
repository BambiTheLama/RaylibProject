#pragma once
#include "raylib.h"
#include "../../Core/Controller.h"

class GameObject;
class CharacterController;

class Character {
    CharacterController* controllBy = nullptr;
public:
    ~Character();

    virtual void move(Vector2 dir, float deltaTime) = 0;

    virtual void action(Input input, Vector2 dir,float deltaTime) = 0;

    bool canBeControllerd(CharacterController* c);

    void setController(CharacterController* c);

    virtual void destoryController();
};

