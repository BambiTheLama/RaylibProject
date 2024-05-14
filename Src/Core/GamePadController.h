//
// Created by Szymek on 15.05.2024.
//

#ifndef GAMEPADCONTROLLER_H
#define GAMEPADCONTROLLER_H
#include "Controller.h"


class GamePadController : public Controller {
public:
    void update(float deltaTime);
};


#endif //GAMEPADCONTROLLER_H
