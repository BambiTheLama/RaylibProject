#pragma once
#include "Controller.h"

class GameObject;

enum class Action
{
    NON    = 0b000,
    Run    = 0b001,
    Attack = 0b010,
    GoTo   = 0b100,
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

    void update(float deltaTime);

    void lookForTarget();


};

