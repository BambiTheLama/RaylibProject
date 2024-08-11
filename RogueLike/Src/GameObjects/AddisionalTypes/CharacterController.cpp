#include "CharacterController.h"
#include "../../Core/Controller/GamePadController.h"
#include "../../Core/Controller/KeyBoardController.h"


CharacterController::CharacterController() {
    setController(new KeyBoardController());
    //setController(new GamePadController());
    this->type = type;
}

CharacterController::~CharacterController() {
    if (this->controller)
        delete controller;
    controller = nullptr;
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
    Vector2 moveDir = controller->getMoveDir();
    Vector2 inputDir = controller->getInputDir();
    for (auto i : inputs)
        character->action(i, moveDir, inputDir, deltaTime);

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
    if (controller)
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

Vector2 CharacterController::getCursorDir()
{
    if (!controller)
        return { 0,0 };
    return controller->getInputDir();
}

void CharacterController::setCharacterType(ObjectType type)
{ 
    this->type = type; 
    if (gm)
        gm->setType(type);

}
