#include "Weapon.h"
#include "../GameObject.h"

Weapon::Weapon()
{

}

void Weapon::update() 
{ 
	if (thisObj)
		thisObj->update(0.0f);
	else
		findThisObject();
}

bool Weapon::triggerNode(WeaponNodeActivation activation)
{
	if (!thisObj)
		findThisObject();
	if (!thisObj)
		return false;
	printf("U¿yto %d\n", (int)activation);
	return weaponNodeTrigger.activateTrigger(activation, thisObj);
	return false;
}

void Weapon::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
}