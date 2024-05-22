#pragma once
#include "Character.h"
#include "../../Core/Controller.h"


class CharacterController {
    Controller *controller;
    Character *character = nullptr;
    GameObject* gm;
    Vector2 pos = { 0,0 };
public:
    CharacterController();

    ~CharacterController();

    void update(float deltaTime);

    void setCharacter(Character* character);

    void setController(Controller* controller);

    void destoryController();

    bool hasController() { return controller; }

    Vector2 getPos() { return pos; }
};

