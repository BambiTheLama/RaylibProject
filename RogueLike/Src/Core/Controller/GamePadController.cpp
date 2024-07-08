#include "GamePadController.h"


void GamePadController::update(float deltaTime) {
    inputs.clear();
    if (controllAction)
    {
        Controller::update(deltaTime);
        return;
    }
    int gamepad = 0;
    moveDir = {
        GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y)
    };

    inputDir = {
        GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y)
    };
    if(IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP))
        inputs.push_back(Input::Attack1);
}
