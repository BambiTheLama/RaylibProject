#pragma once
#include "Controller.h"
#include "raylib.hpp"
#define ControllsSize 1

class KeyBoardController : public Controller {
    int keyUP = KEY_W;
    int keyDown = KEY_S;
    int keyLeft = KEY_A;
    int keyRight = KEY_D;
    int keyAttack1 =  KEY_SPACE;
    int keyInteract = KEY_F;
    int keyNextItem =  KEY_E;
    int keyPrivItem =  KEY_Q;
    int keyItemInHand = KEY_ONE;
    int keySpawnDescriptionVisible = KEY_TAB;
public:
    void update(float deltaTime) override;
};
