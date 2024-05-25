#include "CollisionElementLines.h"
#include "../../../Core/WaveCollapsFun.h"

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
        for (int i = 0; i < points.size() - 1; i++) {
            if (CheckCollisionRecLine(rec, points[i], points[i + 1]))
                return true;
        }

        return CheckCollisionRecLine(rec, points[0], points[points.size() - 1]);
    }
    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> points2 = collisionElement->getLines(collisionElementPos);
        return CheckCollisionLines(points, points2);
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 sCircle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircleLines({sCircle.x, sCircle.y}, sCircle.z, points);
    }
}
Dir CollisionElementLines::getCollisionDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos)
{
    std::vector<Vector2> points = getLines(thisPos);
    if (collisionElement->getType() == CollisionType::Box) {
        Rectangle rec = collisionElement->getBox(collisionElementPos);
        for (int i = 0; i < points.size() - 1; i++) {
            Dir d = CheckCollisionRecLineDir(rec, points[i], points[i + 1]);
            if (d != Dir::NON)
                return swapDir(d);
        }
        return swapDir(CheckCollisionRecLineDir(rec, points[0], points[points.size() - 1]));
    }

    return Dir::NON;
}