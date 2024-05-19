#include "Character.h"
#include "CharacterController.h"

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
        controllBy = c;
}

void Character::destoryController()
{

}