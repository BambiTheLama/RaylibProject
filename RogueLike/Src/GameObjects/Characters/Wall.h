#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../Collider/CollisionElementLines.h"
#include "iostream"
#include "../AddisionalTypes/Hitable.h"
#include <vector>
#include "raylib.hpp"

extern const float tileW;
extern const float tileH;

class Wall : public GameObject, public Collider{
    TextureController texture;
public:
    Wall(Rectangle pos);

    Wall(float x, float y, float w = tileW, float h = tileH);

    ~Wall();

    void start() override;

    void update(float deltaTime);

    void draw() override;

    void onCollisionEnter(Collider* collider) override;

    void onCollisionExit(Collider* collider) override;

    void deletePartWall(Rectangle toDelete);

    void updateCollison();
};
