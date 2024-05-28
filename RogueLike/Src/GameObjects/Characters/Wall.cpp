#include "Wall.h"
#include "../../Core/Floor/Room.h"
#include "rlgl.h"


Wall::Wall(int x, int y) {
    
        
    pos = { (float)x, (float)y, tileW, tileH };
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
    solidObject = true;
    moving = false;
    mass = 10000;
}

Wall::~Wall()
{
}


void Wall::update(float deltaTime) {
}

void Wall::draw(){ 
    DrawRectangleRec(pos, RED); 
    DrawRectangleLinesEx(pos,3, BLACK);
}

void Wall::onCollisionEnter(Collider* collider) {
    
}

void Wall::onCollisionExit(Collider* collider){

}