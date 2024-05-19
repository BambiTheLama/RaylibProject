#pragma once
class Hitable {
protected:
    float hp = 0;
    float invisibleFrames = 0.0f;
public:
    bool dealDamage(float damage, float invisibleFrames = 0.1f);

    void update(float deltaTime);

    virtual void onHit(){}

    virtual void deadTrigger();
};

