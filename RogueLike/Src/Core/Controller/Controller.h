#pragma once
#include <vector>
#include "raylib.hpp"

enum class Input {
    NON,
    Interact, 
    Attack1, 
    Attack2, 
    IDE, 
    NextItem, 
    PrivItem,
    SwapDescriptionVisible,
    SetItemInHand
};

enum class Action
{
    NON       = 0b0,
    RunFrom   = 0b1,
    Attack    = 0b10,
    GoTo      = 0b100,
    IDE       = 0b1000,
    TrigerOn  = 0b10000,
    TrigerOff = 0b100000,
    ForcesOff = 0b1000000, 
    ForcesOn  = 0b10000000,
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
    GameObject* gm = nullptr;
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

    void clearInputs();

};

