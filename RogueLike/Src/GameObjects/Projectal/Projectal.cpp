#include "Projectal.h"
#include "../GameObject.h"

bool Projectal::triggerNode(WeaponNodeActivation activation)
{
	if (!thisObj && !findThisObject())
		return false;
	return weaponNodeTrigger.activateTrigger(activation, thisObj);
}

bool Projectal::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
	if (!thisObj)
		return false;
	return true;
}