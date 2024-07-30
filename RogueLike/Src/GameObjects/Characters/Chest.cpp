#include "Chest.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
extern const float tileW;
extern const float tileH;

Chest::Chest(Rectangle pos, int tier)
{
	pos.width = tileW;
	pos.height = tileH;
	this->pos = pos;
	addCollisionElement(new CollisionElementLines({ 0,0,pos.width,pos.height }));
	solidObject = true;
	moving = false;
	mass = 100;
}

void Chest::draw()
{
	if (isClosestObject)
	{
		const float moveBy = 5.0f;
		startOutLineShader();
		draw(moveRectangeBy(pos, { moveBy,0 }));
		draw(moveRectangeBy(pos, { -moveBy,0 }));
		draw(moveRectangeBy(pos, { 0,-moveBy }));
		draw(moveRectangeBy(pos, { 0,moveBy }));
		EndShaderMode();
	}

	draw(pos);
	
}

void Chest::draw(Rectangle pos)
{
	DrawFrameRec(pos);
}

void Chest::interact(GameObject* interactObj)
{
	Game::deleteObject(this);
}

