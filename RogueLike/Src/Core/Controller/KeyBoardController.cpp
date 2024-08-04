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
        if (IsKeyDown(keyAttack))
            inputs.push_back(Input::Attack);
        if (IsKeyReleased(keyAttack))
            inputs.push_back(Input::StopAttack);
        if (IsKeyPressed(keyBomb))
            inputs.push_back(Input::Bomb);
        if (IsKeyPressed(keyNextItem))
            inputs.push_back(Input::NextItem);
        if (IsKeyPressed(keyPrivItem))
            inputs.push_back(Input::PrivItem);
        if (IsKeyPressed(keySpawnDescriptionVisible))
            inputs.push_back(Input::SwapDescriptionVisible);
        if (IsKeyPressed(dropItem))
            inputs.push_back(Input::DropItem);
        if(IsKeyPressed(keyItemInHand))
            inputs.push_back(Input::SetItemInHand);
        if (IsKeyPressed(keyInteract))
            inputs.push_back(Input::Interact);
        float scrol = GetMouseWheelMove();
        if (scrol == 0)
            ;
        else if(scrol>0)
            inputs.push_back(Input::NextItem);
        else
            inputs.push_back(Input::PrivItem);

        
    }
    moveDir = Vector2Normalize(moveDir);


    inputDir = GetMousePosition();
    inputDir.x -= GetScreenWidth() / 2;
    inputDir.y -= GetScreenHeight() / 2;
    inputDir = Vector2Normalize(inputDir);
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        inputs.push_back(Input::Attack);
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        inputs.push_back(Input::StopAttack);
}
