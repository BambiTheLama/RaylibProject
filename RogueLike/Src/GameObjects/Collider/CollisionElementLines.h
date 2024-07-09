#pragma once
#include "CollisionElement.h"


class CollisionElementLines : public CollisionElement {
    std::vector<Vector2> lines;
    float angle = 0.0f;
    Vector2 rotationPoint;
    bool mirror = false;
public:
    CollisionElementLines(std::vector<Vector2> lines);

    void update(GameObject* gm, bool mirror);

    std::vector<Vector2> getLines(Vector2 pos) override;

    void setRotateAngle(float angle) { this->angle = angle; }

    void setRotationPoint(Vector2 point) { this->rotationPoint = point; }

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos, Vector2* dir, float* depht) override;

    void scaleElement(float scale);

    virtual Vector2 getMinPos() override;

    virtual Vector2 getMaxPos() override;
};

