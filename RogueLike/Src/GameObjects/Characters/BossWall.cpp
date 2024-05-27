#include "BossWall.h"
#include "../../Core/Floor/Room.h"

BossWall::BossWall(int x, int y)
{
    pos = { (float)x, (float)y, tileW, tileH };
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
    solidObject = true;
    moving = false;
    mass = 10000;
}

void BossWall::update(float deltaTime)
{

}

void BossWall::draw()
{
	DrawRectangleRec(getPos(), { 128,0,0,255 });
}