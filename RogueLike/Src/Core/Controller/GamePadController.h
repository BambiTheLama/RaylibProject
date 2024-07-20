#pragma once
#include "Controller.h"


class GamePadController : public Controller {
public:
    GamePadController();

    ~GamePadController();

    void update(float deltaTime);
};

