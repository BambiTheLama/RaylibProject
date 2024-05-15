//
// Created by Szymek on 15.05.2024.
//

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H
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


#endif //CHARACTERCONTROLLER_H
