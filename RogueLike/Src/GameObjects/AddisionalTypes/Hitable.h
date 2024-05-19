#pragma once
#include "raylib.h"
class Hitable {

protected:
    float maxHp = 0;
    float hp = 0;
    float invisibleFrames = 0.0f;
public:
    Hitable(int hp = 10);

    bool dealDamage(float damage, float invisibleFrames = 0.1f);

    void update(float deltaTime);

    virtual void onHit(){}

    virtual void deadTrigger();

    float getProcentHp() { return hp / maxHp; }

    void draw(Rectangle pos);
};

