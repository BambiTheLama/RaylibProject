#include "CharacterController.h"
#include "../../Core/GamePadController.h"
#include "../../Core/KeyBoardController.h"


CharacterController::CharacterController() {
    setController(new KeyBoardController());
    this->type = type;
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
    if (gm)
    {
        Rectangle rec = gm->getPos();
        pos = { rec.x + rec.width / 2,rec.y + rec.height / 2 };
    }

    std::vector<Input> inputs = controller->getInputs();

    for (auto i : inputs)
        character->action(i, controller->getMoveDir(), deltaTime);
}

void CharacterController::setCharacter(Character* character) 
{ 
    this->character = character; 
    if (character)
        character->setController(this); 
    GameObject* gm = dynamic_cast<GameObject*>(character);
    if (gm)
    {
        this->gm = gm;
        gm->setType(type);

    }
    controller->setGameObject(gm);

}

void CharacterController::setController(Controller* controller) 
{ 
    if (!controller)
        return; 
    if (this->controller)
        delete this->controller;
    this->controller = controller; 
}

bool CharacterController::setControllAction(ControllAction* action)
{
    if (!controller)
        return false;
    return controller->setControllAction(action);
}

void CharacterController::destoryController()
{
    if (this->controller)
    {
        delete this->controller;
        this->controller = nullptr;
    }

}

void CharacterController::setCharacterType(ObjectType type)
{ 
    this->type = type; 
    if (gm)
        gm->setType(type);

}
