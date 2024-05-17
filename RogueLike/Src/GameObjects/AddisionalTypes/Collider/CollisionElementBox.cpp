#include "CollisionElementBox.h"

CollisionElementBox::CollisionElementBox(Rectangle col) : CollisionElement(CollisionType::Box) {
    this->col = col;
}

bool CollisionElementBox::isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement,
                                           Vector2 collisionElementPos) {
    Rectangle thisBox = getBox(thisPos);
    if (collisionElement->getType() == CollisionType::Box) {
        Rectangle otherBox = collisionElement->getBox(collisionElementPos);
        return CheckCollisionRecs(thisBox, otherBox);
    }
    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> lines = collisionElement->getLines(collisionElementPos);
        for (int i = 0; i < lines.size() - 1; i++) {
            if (CheckCollisionRecLine(thisBox, lines[i], lines[i + 1]))
                return true;
        }
        if (CheckCollisionRecLine(thisBox, lines[0], lines[lines.size() - 1]))
            return true;
        return false;
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 circle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircleRec({circle.x, circle.y}, circle.z, thisBox);
    }
    return false;
}

