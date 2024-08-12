#pragma once
#include "raylib.hpp"
#include "../../Core/Controller/Controller.h"
//#include "CharacterController.h"

class GameObject;
class CharacterController;

class Character {
    CharacterController* controllBy = nullptr;
    GameObject* thisObj = nullptr;
public:
    ~Character();

    virtual void move(Vector2 dir, float deltaTime);

    virtual void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime);

    bool canBeControllerd(CharacterController* c);

    void setController(CharacterController* c);

    bool setController(Controller* c);

    Vector2 getcursorDir();

    CharacterController* getCharacterController() { return controllBy; }

    virtual void destoryController();
};

