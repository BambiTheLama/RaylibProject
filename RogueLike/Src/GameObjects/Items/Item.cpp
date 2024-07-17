#include "Item.h"

bool Item::showDescriptions = false;

void Item::update(float deltaTime) 
{
	if (thisObj)
		thisObj->update(deltaTime);
	else
		findThisObject();
}

void Item::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
}