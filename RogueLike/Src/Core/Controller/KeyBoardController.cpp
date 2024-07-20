#include "KeyBoardController.h"
#include <math.h>
#include "raymath.h"
void KeyBoardController::update(float deltaTime) {

    if (controllAction)
    {
        Controller::update(deltaTime);
        return;
    }
        clearInputs();
    moveDir = {0, 0};
    for (int i = 0; i < ControllsSize; i++) {
        if (IsKeyDown(keyUP))
            moveDir.y -= 1;
        if (IsKeyDown(keyDown))
            moveDir.y += 1;
        if (IsKeyDown(keyRight))
            moveDir.x += 1;
        if (IsKeyDown(keyLeft))
            moveDir.x -= 1;

        if (IsKeyPressed(keyUP))
            inputs.push_back(Input::UpSlot);
        if (IsKeyPressed(keyDown))
            inputs.push_back(Input::DownSlot);
        if (IsKeyPressed(keyRight))
            inputs.push_back(Input::NextSlot);
        if (IsKeyPressed(keyLeft))
            inputs.push_back(Input::PrivSlot);
        if (IsKeyDown(keyAttack1))
            inputs.push_back(Input::Attack1);
        if (IsKeyPressed(keyNextItem))
            inputs.push_back(Input::NextItem);
        if (IsKeyPressed(keyPrivItem))
            inputs.push_back(Input::PrivItem);
        if (IsKeyPressed(keySpawnDescriptionVisible))
            inputs.push_back(Input::SwapDescriptionVisible);
        if(IsKeyPressed(keyItemInHand))
            inputs.push_back(Input::SetItemInHand);
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
