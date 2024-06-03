#include "GamePadController.h"


void GamePadController::update(float deltaTime) {
    if (controllAction)
    {
        Controller::update(deltaTime);
        return;
    }
    int gamepad = 0;
    moveDir = {
        GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y)
    };
}
