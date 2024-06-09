#pragma once
#include <vector>

#include "raylib.hpp"

enum class Input {
    Interact, Attack1, Attack2, IDE
};

enum class Action
{
    NON       = 0b000000,
    RunFrom   = 0b000001,
    Attack    = 0b000010,
    GoTo      = 0b000100,
    IDE       = 0b001000,
    TrigerOn  = 0b010000,
    TrigerOff = 0b100000,
};

struct ControllAction
{
    float time;
    Vector2 dir;
    Action action;
    ControllAction* nextAcction = nullptr;
};

class GameObject;
class Controller {
protected:
    GameObject* gm;
    Vector2 moveDir = { 0,0 };
    Vector2 inputDir = { 0,0 };
    std::vector<Input> inputs;
    ControllAction* controllAction = nullptr;
public:
    virtual void update(float deltaTime);

    bool setControllAction(ControllAction* action);

    Vector2 getMoveDir() const { return moveDir; }

    std::vector<Input> getInputs() const { return inputs; }

    Vector2 getInputDir()const { return inputDir; }

    void setGameObject(GameObject* gm) { this->gm = gm; }

};

