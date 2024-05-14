//
// Created by szymek on 14.05.2024.
//

#include "Player.h"

Player::Player(int x, int y) {
    pos={(float)x,(float)y,10,10};
}

void Player::update(float deltaTime)
{
    if(IsKeyDown(KEY_W))
        pos.y-=deltaTime;
    if(IsKeyDown(KEY_S))
        pos.y+=deltaTime;
    if(IsKeyDown(KEY_A))
        pos.x-=deltaTime;
    if(IsKeyDown(KEY_D))
        pos.x+=deltaTime;

}

void Player::draw()
{
    DrawRectangleRec(pos,RED);
}