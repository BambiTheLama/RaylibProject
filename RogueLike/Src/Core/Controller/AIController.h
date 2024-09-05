#pragma once
#include "Controller.h"
#include <list>
#include <string>

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
    Action action = Action::NON;
    Vector2 lastMoveDir = { 0.0f,0.0f };
    float findPathTimer = 0.1f;
    const float refresTimer = 0.69f;

    void update(float deltaTime);

    void lookForTarget();

    void newToGoDir();

    std::string getActionName();

    void setAction(Action action);

    void findPathToObject(GameObject* target);

    bool hasPath() { return toGoDir.size() > 0 || toGoDirNow.z > 0.0f; }

private:
    void readLastMoveData(float deltaTime);

};

