#include "BossWall.h"
#include "../../Core/Floor/Room.h"



BossWall::BossWall()
{
    solidObject = true;
    moving = false;
    mass = 10000;
    type = ObjectType::Wall;
    texture = TextureController("Wall/Wall.png");
}

BossWall::BossWall(float x, float y):BossWall()
{
    pos = { (float)x, (float)y, tileW, tileH };
    addCollisionElement(new CollisionElementLines({ 0.0f,0.0f,pos.width,pos.height }));
}

BossWall::BossWall(float x, float y, float w, float h) :BossWall()
{
    pos = { x, y, w, h };
    addCollisionElement(new CollisionElementLines({ 0.0f,0.0f,pos.width,pos.height }));
}

void BossWall::update(float deltaTime)
{

}

void BossWall::draw()
{
    //DrawRectangleRec(pos, RED);
    //DrawRectangleLinesEx(pos, 2, BLACK);
    float x = pos.x - ((int)(pos.x / tileW)) * tileW;
    float y = pos.y - ((int)(pos.y / tileH)) * tileH;
    texture.drawTile(pos, x, y, pos.width / tileW, pos.height / tileH);
}