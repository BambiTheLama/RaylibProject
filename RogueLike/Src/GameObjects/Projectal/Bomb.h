#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementCircle.h"

extern const float tileW;
extern const float tileH;

class Bomb :
    public GameObject, public Collider
{
    float damage = 1.0f;
    float time = 1.0f;
    const float timerMax = 2.0f;
    float range = 250.0f;
public:
    Bomb(float x, float y);

    void update(float deltaTime);

    void explode();

    void draw();
};

