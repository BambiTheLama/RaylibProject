#include "CollisionElement.h"
#include <math.h>
#include "raylib.hpp"
#include "../../../Core/WaveCollapsFun.h"


Dir CollisionElement::getCollisionDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos)
{
    return Dir::NON;
}

bool CheckCollisionRecLine(Rectangle rec, Vector2 start, Vector2 end) {
    Vector2 point;
    if (CheckCollisionLines(start, end, {rec.x, rec.y}, {rec.x, rec.y + rec.height}, &point))
        return true;
    if (CheckCollisionLines(start, end, {rec.x, rec.y}, {rec.x + rec.width, rec.y}, &point))
        return true;
    if (CheckCollisionLines(start, end, {rec.x + rec.width, rec.y}, {rec.x + rec.width, rec.y + rec.height}, &point))
        return true;
    if (CheckCollisionLines(start, end, {rec.x, rec.y + rec.height}, {rec.x + rec.width, rec.y + rec.height}, &point))
        return true;
    if (CheckCollisionLines(start, end, {rec.x + rec.width, rec.y}, {rec.x, rec.y + rec.height}, &point))
        return true;
    if (CheckCollisionLines(start, end, {rec.x, rec.y}, {rec.x + rec.width, rec.y + rec.height}, &point))
        return true;
    return false;
}

Dir CheckCollisionRecLineDir(Rectangle rec, Vector2 start, Vector2 end) {
    Vector2 point;
    if (CheckCollisionLines(start, end, { rec.x, rec.y }, { rec.x, rec.y + rec.height }, &point))
        return Dir::Left;
    if (CheckCollisionLines(start, end, { rec.x, rec.y }, { rec.x + rec.width, rec.y }, &point))
        return Dir::Up;
    if (CheckCollisionLines(start, end, { rec.x + rec.width, rec.y }, { rec.x + rec.width, rec.y + rec.height }, &point))
        return Dir::Right;
    if (CheckCollisionLines(start, end, { rec.x, rec.y + rec.height }, { rec.x + rec.width, rec.y + rec.height }, &point))
        return Dir::Down;
    return Dir::NON;
}

bool CheckCollisionCircles(Vector3 p1, Vector3 p2) {
    return CheckCollisionCircles({p1.x, p1.y}, p1.z, {p2.x, p2.y}, p2.z);
}

float distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool CheckCollisionCircleLine(Vector2 v, float radius, Vector2 p1, Vector2 p2) {
    float len = distance(p1.x, p1.y, p2.x, p2.y);
    float dot = (((v.x - p2.x) * (p1.x - p2.x)) + ((v.y - p2.y) * (p1.y - p2.y))) / pow(len, 2);

    float closestX = p2.x + (dot * (p1.x - p2.x));
    float closestY = p2.y + (dot * (p1.y - p2.y));

    if (!CheckCollisionPointLine({closestX, closestY}, p1, p2, 1))
        return false;
    float distX = closestX - v.x;
    float distY = closestY - v.y;
    float distance = sqrt(pow(distX, 2) + pow(distY, 2));
    return distance <= radius;
}

bool CheckCollisionCircleLines(Vector2 v, float radius, std::vector<Vector2> points) {
    if (points.size() <= 1)
        return false;
    for (int i = 0; i < points.size() - 1; i++)
        if (CheckCollisionCircleLine(v, radius, points[i], points[i + 1]))
            return true;
    return CheckCollisionCircleLine(v, radius, points[0], points[points.size() - 1]);
}

bool CheckCollisionLines(std::vector<Vector2> lines1, std::vector<Vector2> lines2) {
    Vector2 line;
    if (lines1.size() <= 1 || lines2.size() <= 1)
        return false;
    for (int i = 0; i < lines1.size(); i++) {
        Vector2 l1 = lines1[i];
        Vector2 l2 = lines1[(i + 1) % lines1.size()];
        for (int j = 0; j < lines2.size() - 1; j++) {
            if (CheckCollisionLines(l1, l2, lines2[j], lines2[j + 1], &line))
                return true;
        }
        if (CheckCollisionLines(l1, l2, lines2[0], lines2[lines2.size() - 1], &line))
            return true;
    }
    return false;
}

#ifdef showColliders
#include "../../GameObject.h"

void CollisionElement::draw(GameObject *obj) {
    Vector3 circle;
    std::vector<Vector2> points;
    switch (type) {
        case CollisionType::Box:
            DrawRectangleRec(getBox(obj->getPosPoint()),{255,0,0,128});
            DrawRectangleLinesEx(getBox(obj->getPosPoint()), 3, { 0,0,0,128 });
            break;
        case CollisionType::Circle:
            circle = getCircle(obj->getPosPoint());
            DrawCircleV({circle.x, circle.y}, circle.z, { 255,0,0,128 });
            DrawCircleLinesV({circle.x, circle.y}, circle.z, { 0,0,0,128 });
            break;
        case CollisionType::Line:
            points = getLines(obj->getPosPoint());
            for (auto i = 0; i < points.size(); i++) {
                Vector2 p1 = points[i];
                Vector2 p2 = points[(i + 1) % points.size()];
                DrawLineEx(p1, p2, 7, { 0,0,0,128 });
                DrawLineEx(p1, p2, 3, { 255,0,0,128 });
            }

            break;
    }
}
#endif
