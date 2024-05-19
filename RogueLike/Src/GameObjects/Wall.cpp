#include "Wall.h"


Wall::Wall(int x, int y) {
    pos = { (float)x, (float)y, 64.0f, 64.0f };
    pos.x -= pos.width / 2;
    pos.y -= pos.height / 2;
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
}

void Wall::update(float deltaTime) {
}

void Wall::draw(){ 
    DrawRectangleRec(pos, RED); 
    DrawRectangleLinesEx(pos,3, BLACK);
}

void Wall::onCollisionEnter(Collider* collider) {
    printf("KURWA111\n");
}

void Wall::onCollisionExit(Collider* collider){
    printf("KURWA111 END\n");
}