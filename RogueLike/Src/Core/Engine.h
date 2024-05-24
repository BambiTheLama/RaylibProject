#pragma once
#include "Scene.h"


class Engine {
    Scene* s = nullptr;

public:
    Engine();

    void setScene(Scene *s);
};

