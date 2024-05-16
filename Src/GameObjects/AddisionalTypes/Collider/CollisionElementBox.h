//
// Created by Szymek on 16.05.2024.
//

#ifndef COLLISIONELEMENTBOX_H
#define COLLISIONELEMENTBOX_H
#include "CollisionElement.h"
#include "raylib.h"


class CollisionElementBox : public CollisionElement {
    Rectangle col;

public:
    CollisionElementBox(Rectangle col);

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos) override;

    Rectangle getBox(Vector2 pos) override { return {col.x + pos.x, col.y + pos.y, col.width, col.height}; }
};


#endif //COLLISIONELEMENTBOX_H
