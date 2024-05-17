#pragma once
#include "Character.h"
#include "../../Core/Controller.h"


class CharacterController {
    Controller *controller;
    Character *character = nullptr;

public:
    CharacterController();

    ~CharacterController();

    void update(float deltaTime);

    void setCharacter(Character *character) { this->character = character; }
};
