#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Hitable.h"
#include "../AddisionalTypes/LightObject.h"
#include "../Collider/Collider.h"
class Torch :
    public GameObject, public Hitable, public LightObject,public Collider
{
    TextureController texture;
    float frameTimer = 0.0f;
public:
    Torch(Rectangle pos);

    void start()override;

    void update(float deltaTime)override;

    void draw()override;

    void onHit()override;
};

