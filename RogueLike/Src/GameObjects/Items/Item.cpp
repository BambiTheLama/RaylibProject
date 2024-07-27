#include "Item.h"

void Item::update(float deltaTime) 
{
	if (thisObj)
		thisObj->update(deltaTime);
	else
		findThisObject();
}

void Item::drawOverLine(Rectangle pos, Color overLine)
{
	startOutLineShader();
	const int lineSize = 4;
	drawIcon({ pos.x - lineSize,pos.y,pos.width,pos.height }, true, overLine);
	drawIcon({ pos.x + lineSize,pos.y,pos.width,pos.height }, true, overLine);
	drawIcon({ pos.x,pos.y + lineSize,pos.width,pos.height }, true, overLine);
	drawIcon({ pos.x,pos.y - lineSize,pos.width,pos.height }, true, overLine);
	EndShaderMode();
	drawIcon(pos, true);
}

void Item::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
}
