#include "LootBlock.h"
#include "../Game.h"
#include "../Collider/CollisionElementCircle.h"

LootBlock::LootBlock(float x, float y)
{
	trigger = true;
	moving = false;
	pos = { x,y,tileW,tileH };
	collisionElemnets.push_back(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.width / 4));
	type = ObjectType::Loot;
}

void LootBlock::update(float deltaTime)
{
	Hitable::update(deltaTime);
}

void LootBlock::draw()
{
	Vector2 cPos = { pos.x + tileW / 2, pos.y + tileH / 2 };
	DrawCircleV(cPos, tileH / 2, ORANGE);
	DrawCircleLinesV(cPos, tileH / 2, BLACK);
	DrawCircleLinesV(cPos, tileH / 4, BLACK);
}

void LootBlock::onTriggerEnter(Collider* collider)
{
	GameObject* gm = collider->getThisObj();
	if (!gm)
		return;
	if (gm->getType() == ObjectType::Player)
		Game::deleteObject(this);
}