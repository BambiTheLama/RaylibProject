#pragma once
#include <vector>

#include "raylib.h"

enum class Input {
    Interact, Attack1, Attack2,
};

class Controller {
protected:
    Vector2 moveDir;
    std::vector<Input> inputs;

public:
    virtual void update(float deltaTime) = 0;

    Vector2 getMoveDir() const { return moveDir; }
    std::vector<Input> getInputs() const { return inputs; }
};

