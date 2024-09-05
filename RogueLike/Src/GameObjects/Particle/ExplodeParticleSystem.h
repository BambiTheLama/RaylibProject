#pragma once
#include "../GameObject.h"
#include <vector>
#include "../AddisionalTypes/LightObject.h"
#include "Particle.h"



class ExplodeParticleSystem:
    public GameObject, public LightObject
{
    float timer = 0.0f;
    std::vector<Particle> particles;
    TextureController texture;
public:
    ExplodeParticleSystem(Vector2 pos, float range, int particles = 100,float timer=1.0f,float speed=100.0f);

    void update(float deltaTime)override;

    void draw()override;

    virtual void drawLight() override;
};

