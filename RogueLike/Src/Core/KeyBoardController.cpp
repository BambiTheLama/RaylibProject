//
// Created by Szymek on 14.05.2024.
//

#include "KeyBoardController.h"
#include <math.h>

void KeyBoardController::update(float deltaTime) {
    moveDir = {0, 0};
    for (int i = 0; i < ControllsSize; i++) {
        if (IsKeyDown(keyUP[i]))
            moveDir.y -= 1;
        if (IsKeyDown(keyDown[i]))
            moveDir.y += 1;
        if (IsKeyDown(keyRight[i]))
            moveDir.x += 1;
        if (IsKeyDown(keyLeft[i]))
            moveDir.x -= 1;
    }
    float dist = pow(moveDir.x, 2) + pow(moveDir.y, 2);
    if (dist > 0) {
        float distSquare = sqrt(dist);
        moveDir.x /= distSquare;
        moveDir.y /= distSquare;
    }
}
