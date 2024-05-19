#pragma once
#include "GameObject.h"
#include <string>

class ParticleText :
    public GameObject
{
    std::string text;
    float lifeTime = 2;
    float lifeTimeMax = 2;
    
public:
    ParticleText(int x, int y, std::string text);

    void update(float deltaTime);

    void draw();
};
