#pragma once
#include "CollisionElement.h"


class CollisionElementLines : public CollisionElement {
    std::vector<Vector2> lines;
    float angle = 0.0f;
    Vector2 rotationPoint = { 0.0f,0.0f };
    bool mirror = false;
public:
    CollisionElementLines(Rectangle col);

    CollisionElementLines(std::vector<Vector2> lines);

    void update(GameObject* gm, bool mirror);

    std::vector<Vector2> getLines(Vector2 pos) override;

    void setRotateAngle(float angle) { this->angle = angle; }

    void flipHorizontalElement(float size);

    void setRotationPoint(Vector2 point) { this->rotationPoint = point; }

    Vector2 getRotationPoint() { return rotationPoint; }

    bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos, Vector2* dir, float* depht) override;

    void scaleElement(float scale);

    virtual Vector2 getMinPos() override;

    virtual Vector2 getMaxPos() override;
};

