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
    int keyInteract = KEY_E;
    int dropItem = KEY_Q;
    int keyNextItem =  0;
    int keyPrivItem =  0;
    int keyItemInHand = 0;
    int keySpawnDescriptionVisible = KEY_TAB;
public:
    void update(float deltaTime) override;
};
