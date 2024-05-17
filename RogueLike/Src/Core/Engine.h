#pragma once
#include "Scene.h"


class Engine {
    Scene *s;

public:
    Engine();

    void setScene(Scene *s);
};

