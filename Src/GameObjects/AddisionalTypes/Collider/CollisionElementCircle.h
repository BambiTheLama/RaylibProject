//
// Created by Szymek on 16.05.2024.
//

#ifndef COLLISIONELEMENTCIRCLE_H
#define COLLISIONELEMENTCIRCLE_H
#include "CollisionElement.h"
#include "raylib.h"


class CollisionElementCircle : public CollisionElement {
    Vector2 point;
    float radius;

public:
    CollisionElementCircle(Vector2 point, float radius);

    Vector3 getCircle(Vector2 pos) override { return {point.x + pos.x, point.y + pos.y, radius}; }

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos) override;
};


#endif //COLLISIONELEMENTCIRCLE_H
