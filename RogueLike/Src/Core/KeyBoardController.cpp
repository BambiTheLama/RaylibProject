#include "KeyBoardController.h"
#include <math.h>
#include "raymath.h"
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
    moveDir = Vector2Normalize(moveDir);
}
