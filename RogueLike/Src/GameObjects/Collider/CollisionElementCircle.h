#pragma once
#include "CollisionElement.h"
#include "raylib.hpp"


class CollisionElementCircle : public CollisionElement {
    Vector2 point;
    float radius;

public:
    CollisionElementCircle(Vector2 point, float radius);

    Vector3 getCircle(Vector2 pos) override { return {point.x + pos.x, point.y + pos.y, radius}; }

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos, Vector2* dir, float* depht) override;

    void scaleElement(float scale);

    virtual Vector2 getMinPos() override;

    virtual Vector2 getMaxPos() override;
};


