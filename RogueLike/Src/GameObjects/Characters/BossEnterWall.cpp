#include "BossEnterWall.h"


BossEnterWall::BossEnterWall(float x, float y, float w, float h)
{
	moving = false;
	pos = Rectangle{ x, y, w, h };
}