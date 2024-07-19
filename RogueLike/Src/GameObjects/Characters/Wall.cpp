#include "Wall.h"
#include "../../Core/Floor/Room.h"
#include "rlgl.h"

Wall::Wall(float x, float y, float w, float h)
{
    solidObject = true;
    moving = false;
    mass = 10000;
    pos = { x, y, w, h };
    std::vector<Vector2> col{
        {0,         0},
        {pos.width, 0},
        {pos.width, pos.height},
        {0,         pos.height }
    };
    collisionElemnets.push_back(new CollisionElementLines(col));
    type = ObjectType::Wall;

}

Wall::~Wall()
{
}


void Wall::update(float deltaTime) {
}

void Wall::draw(){ 
    DrawRectangleRec(pos, RED);
    DrawRectangleLinesEx(pos, 2, BLACK);
}

void Wall::onCollisionEnter(Collider* collider) {
    
}

void Wall::onCollisionExit(Collider* collider){

}