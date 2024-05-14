//
// Created by szymek on 14.05.2024.
//

#include "Player.h"

Player::Player(int x, int y) {
    pos = {(float) x, (float) y, 10, 10};
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
    DrawRectangleRec(pos,RED);
    DrawText(TextFormat("%lf %lf", pos.x, pos.y), 0, 100, 10,RED);
}
