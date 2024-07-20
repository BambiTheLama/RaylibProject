#include "Character.h"
#include "CharacterController.h"
#include "../GameObject.h"

Character::~Character()
{
    if (controllBy)
        controllBy->setCharacter(nullptr);
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


void Character::destoryController()
{

}