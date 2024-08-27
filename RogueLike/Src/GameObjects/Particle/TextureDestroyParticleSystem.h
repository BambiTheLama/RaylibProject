#pragma once
#include "../GameObject.h"

struct TextureDestroyParticle {
    Rectangle pos = { 0,0,1,1 };
    Rectangle textPos = { 0,0,1,1 };
    Vector2 dir = { 0,0 };
    float angle=0.0f;
    float anglePerSec = 0.0f;
    float timer=1.0f;
    float startTime=1.0f;
    float speed = 0.0f;

    void update(float deltaTime);

    void draw(TextureController &texture);
};

class TextureDestroyParticleSystem :
    public GameObject
{
    TextureController texture;
    float timer = 0.0f;
    std::vector<TextureDestroyParticle> particles;
public:
    TextureDestroyParticleSystem(TextureController texture,int frame, Rectangle pos, int w = 3, int h = 3, float timer = 1.0f,float speed=20.0f);

    void update(float deltaTime)override;

    void draw()override;
};

