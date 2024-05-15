//
// Created by szymek on 15.05.2024.
//

#ifndef MYPROJECT_COLLIDER_H
#define MYPROJECT_COLLIDER_H

#include <vector>
#include "raylib.h"

enum class CollisionType{
    Circle,Rectangle
};

class Collider {
    CollisionType type;
    Vector2 rotatePoint;
    std::vector<Vector2> points;

public:
    virtual bool checkCollision(Collider *collider);
};


#endif //MYPROJECT_COLLIDER_H
