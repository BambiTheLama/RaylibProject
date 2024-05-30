#include "SpawnPoint.h"


SpawnPoint::SpawnPoint(float x, float y, BlockType type)
{
	moving = false;
	this->type = type;
	pos = { x,y,tileW,tileH };
}