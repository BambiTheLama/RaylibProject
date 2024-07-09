#include "CollisionElementCircle.h"
#include "raymath.h"

CollisionElementCircle::CollisionElementCircle(Vector2 point, float radius) : CollisionElement(CollisionType::Circle) {
    this->point = point;
    this->radius = radius;
}

bool CollisionElementCircle::isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement,
                                              Vector2 collisionElementPos, Vector2* dir, float* depht) {
    Vector3 circle = getCircle(thisPos);

    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> points = collisionElement->getLines(collisionElementPos);
        if (CheckCollisionCircleLines({ circle.x, circle.y }, circle.z, points, dir, depht))
        {
            dir->x = -dir->x;
            dir->y = -dir->y;
            return true;
        }
        return false;
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 sCircle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircles(circle, sCircle,dir,depht);
    }
    return false;
}
void CollisionElementCircle::scaleElement(float scale)
{
    point = Vector2Scale(point, scale);
    radius *= scale;
}

Vector2 CollisionElementCircle::getMinPos()
{
    return { point.x - radius,point.y - radius };
}

Vector2 CollisionElementCircle::getMaxPos()
{
    return { point.x + radius,point.y + radius };
}