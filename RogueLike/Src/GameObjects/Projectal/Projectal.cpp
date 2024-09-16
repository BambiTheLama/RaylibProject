#include "Projectal.h"
#include "../GameObject.h"
#include "raymath.h"

void Projectal::start()
{
	angle = (Vector2Angle({ 0.0000001f,0.0000001f }, dir)) * RAD2DEG + rotationDiff;
	speed = stats.getSpeed() * 100;
	range = stats.getRange() * 100;
	rangeMax = range;
	pirce = stats.getPirce();
	bounce = stats.getBounce();
}

void Projectal::setDir(Vector2 dir)
{
	this->dir = dir; 	
	angle = (Vector2Angle({ 0.0000001f,0.0000001f }, dir)) * RAD2DEG + rotationDiff;
}

bool Projectal::triggerNode(WeaponNodeActivation activation,WeaponStats stats)
{
	if (!thisObj && !findThisObject())
		return false;
	Rectangle pos = thisObj->getPos();
	return weaponNodeTrigger.activateTrigger(activation, thisObj, stats, { 0,0 }, target);
}

bool Projectal::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
	if (!thisObj)
		return false;
	return true;
}