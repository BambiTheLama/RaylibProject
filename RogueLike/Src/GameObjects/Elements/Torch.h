#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Hitable.h"
#include "../AddisionalTypes/LightObject.h"
#include "../Collider/Collider.h"
#include "../Particle/FierParticle.h"

class Torch :
    public GameObject, public Hitable, public LightObject,public Collider
{
    FierParticle* particle = nullptr;
    TextureController texture;
    float frameTimer = 0.0f;
    bool particleActivated = true;
public:
    Torch(Rectangle pos);

    ~Torch();

    void start()override;

    void destroy()override;

    void update(float deltaTime)override;

    void draw()override;

    void onHit()override;
};

