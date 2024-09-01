#pragma once
#include "raylib.hpp"
#include "math.h"
class Hitable {

protected:
    float maxHp = 1;
    float hp = 1;
    float invisibleFrames = 0.0f;
    const Color hitColor = RED;
    float hitTimer = 0.0f;
    float lastHp = 0;
    float deltaHp = .0f;
    const float hitTimerMax = 0.15f;
public:
    static int showParticle;

    Hitable(float hp = 1.0f);

    void setMaxHp(float maxHp);

    bool dealDamage(float damage, float invisibleFrames = 0.15f);

    void update(float deltaTime);

    virtual void onHit(){}

    virtual void deadTrigger();

    float getProcentHp() { return fmaxf(hp / maxHp, 0.0f); }

    float getAnimateHp() { return fmaxf(lastHp / maxHp, 0.0f); }

    void draw(Rectangle pos);

    virtual bool isAlive() { return hp > 0; }

    Color getHitColor(Color c);
};

