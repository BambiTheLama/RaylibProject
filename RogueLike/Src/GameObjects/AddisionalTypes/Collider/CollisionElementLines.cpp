#include "CollisionElementLines.h"

CollisionElementLines::CollisionElementLines(std::vector<Vector2> lines): CollisionElement(CollisionType::Line) {
    this->lines = lines;
}

std::vector<Vector2> CollisionElementLines::getLines(Vector2 pos) {
    std::vector<Vector2> linesToRet;
    for (auto l: lines)
        linesToRet.push_back({ l.x + pos.x, l.y + pos.y });
    return linesToRet;
}

bool CollisionElementLines::isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement,
                                             Vector2 collisionElementPos) {
    std::vector<Vector2> points = getLines(thisPos);
    if (collisionElement->getType() == CollisionType::Box) {
        Rectangle rec = collisionElement->getBox(collisionElementPos);
        for (int i = 0; i < lines.size() - 1; i++) {
            if (CheckCollisionRecLine(rec, lines[i], lines[i + 1]))
                return true;
        }
        if (CheckCollisionRecLine(rec, lines[0], lines[lines.size() - 1]))
            return true;
        return false;
    }
    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> points2 = collisionElement->getLines(collisionElementPos);
        return CheckCollisionLines(points, points2);
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 sCircle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircleLines({sCircle.x, sCircle.y}, sCircle.z, lines);
    }
}
