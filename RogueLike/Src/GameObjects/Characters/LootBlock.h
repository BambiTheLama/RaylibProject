#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"

extern const float tileW;
extern const float tileH;

class LootBlock :
    public GameObject,public Collider,public Hitable
{
public:
    LootBlock(float x, float y);

    void update(float deltaTime);

    void draw();

    void onTriggerEnter(Collider* collider) override;
};

