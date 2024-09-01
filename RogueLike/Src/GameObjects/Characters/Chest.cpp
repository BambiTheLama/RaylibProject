#include "Chest.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
#include "../Items/ItemFactory.h"
#include "raymath.h"

extern const float tileW;
extern const float tileH;

int Chest::seed = 0;

Chest::Chest(Rectangle pos, int tier)
{
	pos.width = tileW;
	pos.height = tileH;
	this->pos = pos;
	addCollisionElement(new CollisionElementLines({ 0,0,pos.width,pos.height }));
	solidObject = true;
	moving = false;
	mass = 100;
	texture = TextureController("Elements/Chest.png");
}

void Chest::draw()
{
	if (isClosestObject)
	{
		const float moveBy = 2.0f;
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
	//DrawFrameRec(pos);
	texture.draw(pos, false, false, open ? 1 : 0);
}

void Chest::interact(GameObject* interactObj)
{
	if (open)
		return;
	int n = getRandom(seed, 1, 10);
	for (int i = 0; i < n; i++)
	{
		//Weapon* w = getWeapon(0, 0, getRandomWeaponType());
		//if (!w)
		//	continue;
		//GameObject* o = dynamic_cast<GameObject*>(w);
		GameObject* o = getWeaponNode(0, seed);
		if (!o)
		{
			//delete w;
			continue;
		}

		o->setPos(getMidlePoint(moveRectangeBy( pos,Vector2Scale(randVector2(), 10))));
		Game::addObject(o);
	}

	open = true;


	//Game::deleteObject(this);
}

