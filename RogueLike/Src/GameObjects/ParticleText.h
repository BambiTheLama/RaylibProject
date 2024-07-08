#pragma once
#include "GameObject.h"
#include <string>

class ParticleText :
    public GameObject
{
    std::string text;
    float lifeTime = 2;
    float lifeTimeMax = 2;
    Color color;
    float angleRotation = 0.0f;
    float angle = 0.0f;
public:
    ParticleText(float x, float y, float time, std::string text, Color color = RED);

    void update(float deltaTime);

    void draw();
};
