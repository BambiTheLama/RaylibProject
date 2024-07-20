#include "GamePadController.h"
GamePadController::GamePadController()
{
    HideCursor();

}
GamePadController::~GamePadController()
{
    ShowCursor();
}


void GamePadController::update(float deltaTime) {

    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    clearInputs();
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
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
        inputs.push_back(Input::PrivItem);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
        inputs.push_back(Input::NextItem);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
        inputs.push_back(Input::NextSlot);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
        inputs.push_back(Input::PrivSlot);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
        inputs.push_back(Input::UpSlot);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
        inputs.push_back(Input::DownSlot);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
        inputs.push_back(Input::SwapDescriptionVisible);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        inputs.push_back(Input::Interact);
    if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
        inputs.push_back(Input::Attack1);

}
