#include "KeyBoardController.h"
#include <math.h>
#include "raymath.h"
void KeyBoardController::update(float deltaTime) {
    if (controllAction)
    {
        Controller::update(deltaTime);
        return;
    }

    moveDir = {0, 0};
    inputs.clear();
    for (int i = 0; i < ControllsSize; i++) {
        if (IsKeyDown(keyUP))
            moveDir.y -= 1;
        if (IsKeyDown(keyDown))
            moveDir.y += 1;
        if (IsKeyDown(keyRight))
            moveDir.x += 1;
        if (IsKeyDown(keyLeft))
            moveDir.x -= 1;
        if (IsKeyDown(keyAttack1))
            inputs.push_back(Input::Attack1);
        if (IsKeyPressed(keyNextItem))
            inputs.push_back(Input::NextItem);
        if (IsKeyPressed(keyPrivItem))
            inputs.push_back(Input::PrivItem);
    }
    moveDir = Vector2Normalize(moveDir);


    inputDir = GetMousePosition();
    inputDir.x -= GetScreenWidth() / 2;
    inputDir.y -= GetScreenHeight() / 2;
    inputDir = Vector2Normalize(inputDir);
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        inputs.push_back(Input::Attack1);
    }
}
