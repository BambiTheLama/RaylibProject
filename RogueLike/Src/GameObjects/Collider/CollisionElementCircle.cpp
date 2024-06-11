#include "CollisionElementCircle.h"

CollisionElementCircle::CollisionElementCircle(Vector2 point, float radius) : CollisionElement(CollisionType::Circle) {
    this->point = point;
    this->radius = radius;
}

bool CollisionElementCircle::isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement,
                                              Vector2 collisionElementPos, Vector2* dir, float* depht) {
    Vector3 circle = getCircle(thisPos);

    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> points = collisionElement->getLines(collisionElementPos);
        return CheckCollisionCircleLines({circle.x, circle.y}, circle.z, points);
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 sCircle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircles(circle, sCircle);
    }
    return false;
}
