#include "Controller.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/AddisionalTypes/Collider/Collider.h"

void Controller::update(float deltaTime)
{
    if (controllAction)
    {
        inputs.clear();
        controllAction->time -= deltaTime;
        moveDir = { 0,0 };
        switch (controllAction->action)
        {
        case Action::NON:
        case Action::IDE:
            moveDir = { 0,0 };
            break;
        case Action::GoTo:
            moveDir = controllAction->dir;
            break;
        case Action::RunFrom:
            moveDir = controllAction->dir;
            moveDir.x *= -1;
            moveDir.y *= -1;
            break;
        case Action::Attack:
            inputs.push_back(Input::Attack1);
            break;
        case Action::TrigerOn:
        case Action::TrigerOff:
            if (gm)
            {
                Collider* c = dynamic_cast<Collider*>(gm);
                if (c)
                    c->trigger = (Action::TrigerOn == controllAction->action);
                controllAction->time = -1;
            }
            break;
        default:
            break;
        }
        if (controllAction->time <= 0)
        {
            ControllAction* action = controllAction->nextAcction;
            delete controllAction;
            controllAction = action;
        }
    }
}

bool Controller::setControllAction(ControllAction* action)
{
    if (controllAction)
        return false;
    controllAction = action;
    return true;
}