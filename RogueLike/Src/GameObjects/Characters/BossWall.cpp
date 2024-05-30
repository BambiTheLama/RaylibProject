#include "BossWall.h"
#include "../../Core/Floor/Room.h"

BossWall::BossWall()
{

    solidObject = true;
    moving = false;
    mass = 10000;
}

BossWall::BossWall(float x, float y):BossWall()
{
    pos = { (float)x, (float)y, tileW, tileH };
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
}

BossWall::BossWall(int x, int y, int w, int h):BossWall()
{
    pos = { (float)x, (float)y, (float)w, (float)h };
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
}

void BossWall::update(float deltaTime)
{

}

void BossWall::draw()
{
	DrawRectangleRec(getPos(), { 128,0,0,255 });
}