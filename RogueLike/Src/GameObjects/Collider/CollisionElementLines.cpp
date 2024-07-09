#include "CollisionElementLines.h"
#include "../../Core/WaveCollapsFun.h"
#include "../GameObject.h"
#include "raymath.h"

CollisionElementLines::CollisionElementLines(std::vector<Vector2> lines): CollisionElement(CollisionType::Line) {
    this->lines = lines;
}

void CollisionElementLines::update(GameObject* gm, bool mirror)
{
    if (!gm)
        return;
    angle = gm->getAngle() * PI / 180;
    this->mirror = mirror;
    if (mirror)
    {
        angle -= 90 * PI / 180;

    }
    rotationPoint = gm->getRotationPoint();
}

std::vector<Vector2> CollisionElementLines::getLines(Vector2 pos) {

    std::vector<Vector2> linesToRet;
    Vector2 rotationPoint = this->rotationPoint;

    if (mirror)
        rotationPoint.x = -rotationPoint.x;

    for (auto l : lines)
    {
        if (mirror)
        {
            l.x = -l.x;
        }

        float x = cosf(angle) * (l.x - rotationPoint.x) - sinf(angle) * (l.y - rotationPoint.y) + rotationPoint.x;
        float y = sinf(angle) * (l.x - rotationPoint.x) + cosf(angle) * (l.y - rotationPoint.y) + rotationPoint.y;
        Vector2 p = { x + pos.x - rotationPoint.x, y + pos.y - rotationPoint.y };
        linesToRet.push_back(p);


    }

    return linesToRet;
}

bool CollisionElementLines::isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement,
                                             Vector2 collisionElementPos, Vector2* dir, float* depht) {
    std::vector<Vector2> points = getLines(thisPos);

    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> points2 = collisionElement->getLines(collisionElementPos);
        return CheckCollisionLines(points, points2, dir, depht);
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 sCircle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircleLines({ sCircle.x, sCircle.y }, sCircle.z, points, dir, depht);
    }
    return false;
}
void CollisionElementLines::scaleElement(float scale)
{
    std::vector<Vector2> newLines;
    for (auto l : lines)
    {
        newLines.push_back(Vector2Scale(l, scale));
    }
    lines = newLines;
}

Vector2 CollisionElementLines::getMinPos()
{
    if (lines.size() <= 0)
        return { 0.0f,0.0f };
    std::vector<Vector2> lines = getLines({ 0,0 });
    Vector2 minV = lines[0];
    for (int i = 1; i < lines.size(); i++)
    {
        if (lines[i].x < minV.x)
            minV.x = lines[i].x;
        if (lines[i].y < minV.y)
            minV.y = lines[i].y;
    }
    return minV;
}

Vector2 CollisionElementLines::getMaxPos()
{
    if (lines.size() <= 0)
        return { 0.0f,0.0f };
    std::vector<Vector2> lines = getLines({ 0,0 });
    Vector2 maxV = lines[0];
    for (int i = 1; i < lines.size(); i++)
    {
        if (lines[i].x > maxV.x)
            maxV.x = lines[i].x;
        if (lines[i].y > maxV.y)
            maxV.y = lines[i].y;
    }
    return maxV;
}