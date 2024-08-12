#include "Character.h"
#include "CharacterController.h"
#include "../GameObject.h"
#include "raymath.h"

Character::~Character()
{
    if (controllBy)
        controllBy->setCharacter(nullptr);
}

void Character::move(Vector2 dir, float deltaTime)
{
    if (!thisObj)
    {
        thisObj = dynamic_cast<GameObject*>(this);
        if (!thisObj)
            return;
    }
    thisObj->move(Vector2Scale(dir, deltaTime * thisObj->getSpeed()));

}

void Character::action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime)
{
}

bool Character::canBeControllerd(CharacterController* c) 
{ 
    return !controllBy ||  c == controllBy || !controllBy->hasController(); 
}

void Character::setController(CharacterController* c)
{
    if (c != controllBy)
    {
        controllBy = c;
        if (controllBy)
            controllBy->setCharacter(this);
    }

}

bool Character::setController(Controller* c)
{
    if (!controllBy)
        return false;
    controllBy->setController(c);
    return true;
}
Vector2 Character::getcursorDir()
{
    if (!controllBy)
        return { 0,0 };
    return controllBy->getCursorDir();
}

void Character::destoryController()
{

}