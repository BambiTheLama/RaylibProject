#pragma once
#include "Controller.h"
#include <list>

class GameObject;


class AIController :
    public Controller
{
protected:

public:
    GameObject* thisObj = nullptr;
    GameObject* target = nullptr;
    std::list<Vector3> toGoDir;
    Vector3 toGoDirNow = { 0,0,0 };
    int targerType = 0;
    float range = 0;
    int action = 0;
    Vector2 lastMoveDir = { 0.0f,0.0f };
    float findPathTimer = 0.1f;
    const float refresTimer = 1.0f;

    void update(float deltaTime);

    void lookForTarget();

    void newToGoDir();


};

