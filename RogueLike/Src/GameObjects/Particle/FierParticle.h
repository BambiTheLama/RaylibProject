#pragma once
#include "../GameObject.h"
#include "Particle.h"

class FierParticle :
    public GameObject
{
    std::vector<Particle> particle;
    TextureController texture;
public:
    FierParticle(Vector2 pos);

    void update(float deltaTime);

    void draw();

    void resetParticle(Particle& p);
};

