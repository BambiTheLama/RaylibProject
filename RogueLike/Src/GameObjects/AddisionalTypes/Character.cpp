#include "Character.h"
#include "CharacterController.h"

bool Character::canBeControllerd(CharacterController* c) 
{ 
    return !controllBy ||  c == controllBy || !controllBy->hasController(); 
}

void Character::setController(CharacterController* c)
{
    if (!controllBy || c == controllBy)
        controllBy = c;
}

void Character::destoryController()
{

}