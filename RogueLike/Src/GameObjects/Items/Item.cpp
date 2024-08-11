#include "Item.h"
#include "../Characters/Player.h"
#include "../Game.h"

void Item::start()
{
	thisWeapon = dynamic_cast<Weapon*>(this);
}

void Item::update(float deltaTime)
{
	GameObject* o = getThisObj();
	if (o)
		o->update(deltaTime);
}

void Item::interact(GameObject* interactObject)
{
	Player* p = dynamic_cast<Player*>(interactObject);
	if (!p)
		return;
	if (p->addItem(this))
		Game::removeObject(getThisObj());
}

#pragma region DrawFun
void Item::drawOverLine(Rectangle pos, Color overLine, float overlineSize)
{
	startOutLineShader();
	drawIcon({ pos.x - overlineSize,pos.y,pos.width,pos.height }, true, overLine);
	drawIcon({ pos.x + overlineSize,pos.y,pos.width,pos.height }, true, overLine);
	drawIcon({ pos.x,pos.y + overlineSize,pos.width,pos.height }, true, overLine);
	drawIcon({ pos.x,pos.y - overlineSize,pos.width,pos.height }, true, overLine);
	EndShaderMode();
}

void Item::drawDescription(Rectangle pos, float textSize)
{
	if (!thisWeapon)
		return;
	thisWeapon->drawWeaponDescription(pos, textSize);
}
#pragma endregion DrawFun



GameObject* Item::getThisObj()
{
	if (!thisObj)
		thisObj = dynamic_cast<GameObject*>(this);
	return thisObj;
}
