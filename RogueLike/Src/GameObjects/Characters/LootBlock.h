#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Collider/Collider.h"
extern const float tileW;
extern const float tileH;

class LootBlock :
    public GameObject,public Collider
{
public:
    LootBlock(float x, float y);

    void draw();

    void onTriggerEnter(Collider* collider) override;
};

