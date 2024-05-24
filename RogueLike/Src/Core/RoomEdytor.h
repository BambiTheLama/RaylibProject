#pragma once
#include "Scene.h"

class RoomEdytor :
    public Scene
{
public:
    RoomEdytor();

    void start();

    void update(float deltaTime);

    void draw();
};

