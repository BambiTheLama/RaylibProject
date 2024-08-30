#pragma once
#include "../GameObject.h"
#include <vector>

struct ExplodeParticle {
    Vector2 pos = { .0f, .0f };
    Vector2 dir = { .0f, .0f };
    float size = .0f;
    float deltaSize = 0.0f;
    float speed = .0f;
    float acceleration = .0f;
    float angle = 0.0f;
    float deltaAngle = 0.0f;
    float timer = .1f;
    float timerMax = .1f;
    std::vector<Color> colors = { {255,255,0,255},{255,0,0,160},{0,0,0,60},{80,80,80,0} };
    
    void update(float deltaTime);

    Color getColor();

    void draw(TextureController& texture);
};


class ExplodeParticleSystem:
    public GameObject
{
    float timer = 0.0f;
    std::vector<ExplodeParticle> particles;
    TextureController texture;
public:
    ExplodeParticleSystem(Vector2 pos, float range, int particles = 100,float timer=1.0f,float speed=100.0f);

    void update(float deltaTime)override;

    void draw()override;
};

