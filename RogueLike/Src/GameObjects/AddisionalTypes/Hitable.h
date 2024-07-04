#pragma once
#include "raylib.hpp"
class Hitable {

protected:
    float maxHp = 0;
    float hp = 0;
    float invisibleFrames = 0.0f;
public:
    static int showParticle;

    Hitable(float hp = 10.0f);

    bool dealDamage(float damage, float invisibleFrames = 0.1f);

    void update(float deltaTime);

    virtual void onHit(){}

    virtual void deadTrigger();

    float getProcentHp() { return hp / maxHp; }

    void draw(Rectangle pos);

    bool isAlive() { return hp > 0; }
};

