#include "Player.h"
#include "AddisionalTypes/Collider/CollisionElementLines.h"
#include "AddisionalTypes/Collider/CollisionElementBox.h"
#include "AddisionalTypes/Collider/CollisionElementCircle.h"

Player::Player(int x, int y){
    pos = {(float) x, (float) y, 48, 64};
    pos.x -= pos.width / 2;
    pos.y -= pos.height / 2;
    collisionElemnets.push_back(new CollisionElementBox({ pos.width / 4, pos.height /4, pos.width/2, pos.height/2}));
    //drawOrder = 10;
    type = ObjectType::Player;
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

}

void Player::onCollisionExit(Collider* collider) { 

}