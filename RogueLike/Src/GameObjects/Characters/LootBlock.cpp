#include "LootBlock.h"


LootBlock::LootBlock(float x, float y)
{
	moving = false;
	pos = { x,y,tileW,tileH };
}

void LootBlock::draw()
{
	Vector2 cPos = { pos.x + tileW / 2, pos.y + tileH / 2 };
	DrawCircleV(cPos, tileH / 2, ORANGE);
	DrawCircleLinesV(cPos, tileH / 2, BLACK);
	DrawCircleLinesV(cPos, tileH / 4, BLACK);
}