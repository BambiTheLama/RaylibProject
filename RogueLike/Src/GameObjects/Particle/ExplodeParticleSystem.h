#pragma once
#include "../GameObject.h"
#include <vector>

struct ExplodeParticle {
    Vector2 pos = { .0f, .0f };
    Vector2 dir = { .0f, .0f };
    float size = .0f;
    float speed = .0f;
    float acceleration = .0f;
    float timer = .1f;
    float timerMax = .1f;
    std::vector<Color> colors = { YELLOW,RED,BLACK,BLANK };
    
    void update(float deltaTime);

    Color getColor();

    void draw();
};


class ExplodeParticleSystem:
    public GameObject
{
    float timer = 0.0f;
    std::vector<ExplodeParticle> particles;
public:
    ExplodeParticleSystem(Rectangle pos, int particles = 100,int timer=1.0f);

    void update(float deltaTime)override;

    void draw()override;
};

