#include "LootBlock.h"
#include "../Game.h"
#include "../Collider/CollisionElementCircle.h"

LootBlock::LootBlock(Rectangle pos)
{
	//trigger = true;
	solidObject = true;
	moving = false;
	this->pos = pos;
	addCollisionElement(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.width / 4));
	type = ObjectType::Loot;
	mass = 100;
}

LootBlock::~LootBlock()
{
	Game::toCheckPos(pos);
}

void LootBlock::start()
{
	Game::toCheckPos(pos);
	//LightObject::setRange(300);
	//LightObject::colorCenter = ORANGE;
	//LightObject::colorEnd = WHITE;

}

void LootBlock::update(float deltaTime)
{
	Hitable::update(deltaTime);
	//LightObject::update(deltaTime);
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

}