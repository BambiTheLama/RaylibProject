#include "Projectal.h"
#include "../GameObject.h"

bool Projectal::triggerNode(WeaponNodeActivation activation,WeaponStats stats)
{
	if (!thisObj && !findThisObject())
		return false;
	Rectangle pos = thisObj->getPos();
	return weaponNodeTrigger.activateTrigger(activation, thisObj, stats, { 0,0 });
}

bool Projectal::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
	if (!thisObj)
		return false;
	return true;
}