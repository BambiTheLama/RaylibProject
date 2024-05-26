#pragma once
#include "Character.h"
#include "../../Core/Controller.h"
#include "../GameObject.h"

class CharacterController {
    Controller* controller = nullptr;
    Character* character = nullptr;
    GameObject* gm = nullptr;
    Vector2 pos = { 0,0 };
    ObjectType type = ObjectType::NON;
public:
    CharacterController();

    ~CharacterController();

    void update(float deltaTime);

    void setCharacter(Character* character);

    void setController(Controller* controller);

    void destoryController();

    bool hasController() { return controller; }

    Vector2 getPos() { return pos; }

    void setCharacterType(ObjectType type) { this->type = type; }

    bool hasCharacter() { return character; }
};

