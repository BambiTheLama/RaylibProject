#pragma once
#include "Controller.h"

class GameObject;

enum class Action
{
    NON    = 0b0000,
    Run    = 0b0001,
    Attack = 0b0010,
    GoTo   = 0b0100,
    IDE    = 0b1000,
};
class AIController :
    public Controller
{
protected:

public:
    GameObject* thisObj = nullptr;
    GameObject* target = nullptr;
    int targerType = 0;
    int range = 0;
    int action = 0;
    Vector2 IDEMoveDir = { 0,0 };

    void update(float deltaTime);

    void lookForTarget();


};

