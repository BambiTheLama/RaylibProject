#pragma once
#include "Controller.h"

class GameObject;


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
    Vector2 lastMoveDir = { 0.0f,0.0f };
    float findPathTimer = 0.1f;
    const float refresTimer = 0.2f;

    void update(float deltaTime);

    void lookForTarget();


};

