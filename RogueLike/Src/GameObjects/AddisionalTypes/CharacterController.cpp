//
// Created by Szymek on 15.05.2024.
//

#include "CharacterController.h"

#include "../../Core/GamePadController.h"
#include "../../Core/KeyBoardController.h"

CharacterController::CharacterController() {
    controller = new KeyBoardController();
    //controller = new GamePadController();
}

CharacterController::~CharacterController() {
    delete controller;
}


void CharacterController::update(float deltaTime) {
    controller->update(deltaTime);
    if (!character)
        return;
    character->move(controller->getMoveDir(), deltaTime);
    std::vector<Input> inputs = controller->getInputs();
    for (auto i: inputs)
        character->action(i);
}
