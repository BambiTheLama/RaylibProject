#include "Item.h"
#include "../Characters/Player.h"
#include "../Game.h"

void Item::update(float deltaTime) 
{
	GameObject* o = getThisObj();
	if (o)
		o->update(deltaTime);
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

void Item::interact(GameObject* interactObject)
{
	Player* p = dynamic_cast<Player*>(interactObject);
	if (!p)
		return;
	if (p->addItem(this))
		Game::removeObject(getThisObj());
}

GameObject* Item::getThisObj()
{
	if (!thisObj)
		thisObj = dynamic_cast<GameObject*>(this);
	return thisObj;
}
