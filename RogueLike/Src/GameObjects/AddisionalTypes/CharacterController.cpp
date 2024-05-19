#include "CharacterController.h"

#include "../../Core/GamePadController.h"
#include "../../Core/KeyBoardController.h"

CharacterController::CharacterController() {
    controller = new KeyBoardController();
    //controller = new GamePadController();
}

CharacterController::~CharacterController() {
    if (this->controller)
        delete controller;
}


void CharacterController::update(float deltaTime) {
    if (!controller)
        return;
    controller->update(deltaTime);
    if (!character)
        return;
    character->move(controller->getMoveDir(), deltaTime);
    std::vector<Input> inputs = controller->getInputs();
    for (auto i: inputs)
        character->action(i);
}

void CharacterController::setCharacter(Character* character) 
{ 
    this->character = character; 
    character->setController(this); 
}

void CharacterController::setController(Controller* controller) 
{ 
    if (!controller)
        return; 
    if (this->controller)
        delete this->controller;
    this->controller = controller; 
}

void CharacterController::destoryController()
{
    if (this->controller)
    {
        delete this->controller;
        this->controller = nullptr;
    }

}