//
// Created by Szymek on 16.05.2024.
//

#ifndef COLLISIONELEMENTLINES_H
#define COLLISIONELEMENTLINES_H
#include "CollisionElement.h"


class CollisionElementLines : public CollisionElement {
    std::vector<Vector2> lines;

public:
    CollisionElementLines(std::vector<Vector2> lines);

    std::vector<Vector2> getLines(Vector2 pos) override;

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos) override;
};


#endif //COLLISIONELEMENTLINES_H
