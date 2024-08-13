#pragma once
#include "raylib.hpp"
#include "math.h"
class Hitable {

protected:
    float maxHp = 0;
    float hp = 0;
    float invisibleFrames = 0.0f;
public:
    static int showParticle;

    Hitable(float hp = 1.0f);

    bool dealDamage(float damage, float invisibleFrames = 0.01f);

    void update(float deltaTime);

    virtual void onHit(){}

    virtual void deadTrigger();

    float getProcentHp() { return fmaxf(hp / maxHp, 0.0f); }

    void draw(Rectangle pos);

    virtual bool isAlive() { return hp > 0; }
};

