#pragma once
#include "raylib.hpp"
#include "../../Core/Controller/Controller.h"
//#include "CharacterController.h"

class GameObject;
class CharacterController;

class Character {
    CharacterController* controllBy = nullptr;
public:
    ~Character();

    virtual void move(Vector2 dir, float deltaTime) = 0;

    virtual void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime) = 0;

    bool canBeControllerd(CharacterController* c);

    void setController(CharacterController* c);

    void setGameObjectControlled(GameObject* gm);

    bool setController(Controller* c);

    CharacterController* getCharacterController() { return controllBy; }

    virtual void destoryController();
};

