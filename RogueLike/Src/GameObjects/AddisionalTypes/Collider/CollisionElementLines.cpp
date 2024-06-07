#include "CollisionElementLines.h"
#include "../../../Core/WaveCollapsFun.h"
#include "../../GameObject.h"

CollisionElementLines::CollisionElementLines(std::vector<Vector2> lines): CollisionElement(CollisionType::Line) {
    this->lines = lines;
}

void CollisionElementLines::update(GameObject* gm)
{
    if (!gm)
        return;
    angle = gm->getAngle();
    rotationPoint = gm->getRotationPoint();
}

std::vector<Vector2> CollisionElementLines::getLines(Vector2 pos) {

    std::vector<Vector2> linesToRet;
    int angle = this->angle * 3.14159f / 180;
    for (auto l : lines)
    {
        float x = cos(angle) * (l.x - rotationPoint.x) - sin(angle) * (l.y - rotationPoint.y) + rotationPoint.x;
        float y = sin(angle) * (l.x - rotationPoint.x) + cos(angle) * (l.y - rotationPoint.y) + rotationPoint.y;
        linesToRet.push_back({ x + pos.x, y + pos.y });
    }

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