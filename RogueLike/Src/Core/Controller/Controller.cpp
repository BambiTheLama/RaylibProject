#include "Controller.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/Collider/Collider.h"


void Controller::update(float deltaTime)
{
    if (controllAction)
    {
        clearInputs();

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
                    c->trigger = ((int)Action::TrigerOn & (int)controllAction->action);
                controllAction->time = -1;
            }
            break;
        case Action::ForcesOff:
        case Action::ForcesOn:
            if (gm)
            {
                Collider* c = dynamic_cast<Collider*>(gm);
                if (c)
                    c->isResistToForces((int)Action::ForcesOff & (int)controllAction->action);
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

void Controller::clearInputs()
{
    inputs = { Input::NON };
}