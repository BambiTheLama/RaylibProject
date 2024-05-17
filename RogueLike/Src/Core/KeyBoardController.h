#pragma once
#include "Controller.h"
#include "raylib.h"
#define ControllsSize 2

class KeyBoardController : public Controller {
    int keyUP[ControllsSize] = {KEY_W, KEY_UP};
    int keyDown[ControllsSize] = {KEY_S, KEY_DOWN};
    int keyLeft[ControllsSize] = {KEY_A, KEY_LEFT};
    int keyRight[ControllsSize] = {KEY_D, KEY_RIGHT};

public:
    void update(float deltaTime) override;
};
