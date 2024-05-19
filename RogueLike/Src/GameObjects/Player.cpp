#include "Player.h"
#include "AddisionalTypes/Collider/CollisionElementLines.h"
#include "AddisionalTypes/Collider/CollisionElementBox.h"
#include "AddisionalTypes/Collider/CollisionElementCircle.h"

Player::Player(int x, int y) {
    pos = {(float) x, (float) y, 64, 64};
    pos.x -= pos.width / 2;
    pos.y -= pos.height / 2;
    collisionElemnets.push_back(new CollisionElementBox({0, 0, pos.width, pos.height}));
    //drawOrder = 10;
}

Player::~Player() {
}


void Player::update(float deltaTime) {
}

void Player::move(Vector2 dir, float deltaTime) {
    pos.x += dir.x * deltaTime * speed;
    pos.y += dir.y * deltaTime * speed;
}

void Player::action(Input input) {
}


void Player::draw() {
    DrawRectangleRec(pos,BLUE);
    DrawRectangleLinesEx(pos, 2, BLACK);
}

void Player::onCollisionEnter(Collider* collider) { 
    printf("KURWA\n"); 
}

void Player::onCollisionExit(Collider* collider) { 
    printf("KURWA END\n"); 
}