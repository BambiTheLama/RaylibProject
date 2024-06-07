#pragma once
#include "CollisionElement.h"


class CollisionElementLines : public CollisionElement {
    std::vector<Vector2> lines;
    float angle = 0.0f;
    Vector2 rotationPoint;
public:
    CollisionElementLines(std::vector<Vector2> lines);

    void update(GameObject* gm);

    std::vector<Vector2> getLines(Vector2 pos) override;

    void setRotateAngle(float angle) { this->angle = angle; }

    void setRotationPoint(Vector2 point) { this->rotationPoint = point; }

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos) override;

    Dir getCollisionDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos);
};

