#include "Item.h"

void Item::update() 
{
	if (thisObj)
		thisObj->update(0.0f);
	else
		findThisObject();
}

void Item::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
}