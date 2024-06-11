#include "CollisionElement.h"
#include <math.h>
#include "raylib.hpp"
#include "raymath.h"
#include "../../Core/WaveCollapsFun.h"
#include <limits>

Vector2 CollisionElement::getCollisionVectorDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos)
{
    Vector2 dirVector = Vector2Subtract(thisPos, collisionElementPos);
    return Vector2Normalize(dirVector);
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

void projectalCircle(Vector2 v, float radius, Vector2 axies, float* min, float* max)
{
    Vector2 dir = Vector2Scale(Vector2Normalize(axies), radius);
    Vector2 p1 = Vector2Subtract(v, dir);
    Vector2 p2 = Vector2Add(v, dir);
    *min = Vector2DotProduct(p1, axies);
    *max = Vector2DotProduct(p2, axies);
    if (*min > *max)
    {
        float t = *min;
        *min = *max;
        *max = t;
    }
}

void projectalVertices(std::vector<Vector2> lines,Vector2 axies, float* min, float* max)
{
    float dot = Vector2DotProduct(lines[0], axies);
    *min = dot;
    *max = dot;
    for (int i = 1; i < lines.size(); i++)
    {
        dot = Vector2DotProduct(lines[i], axies);
        if (dot < *min)
            *min = dot;
        if (dot > *max)
            *max = dot;
    }
}
int closestPointToCricle(Vector2 v, std::vector<Vector2> lines)
{
    int index = 0;
    float dist = Vector2Distance(v, lines[0]);
    for (int i = 1; i < lines.size(); i++)
    {
        float d = Vector2Distance(v, lines[i]);
        if (d < dist)
        {
            dist = d;
            index = i;
        }
    }
    return index;
}

Vector2 getCenter(std::vector<Vector2> lines)
{
    Vector2 v = { 0,0 };
    if (lines.size() <= 0)
        return v;
    for (auto l : lines)
    {
        v = Vector2Add(v, l);
    }
    return { v.x / lines.size(),v.y / lines.size() };

}

bool CheckCollisionCircleLines(Vector2 v, float radius, std::vector<Vector2> lines, Vector2* dir, float* depth) {
    if (lines.size() <= 0)
        return false;
    Vector2 dirV = { 0,0 };
    float dephtV = std::numeric_limits<float>::max();
    float minA, maxA;
    float minB, maxB;
    Vector2 axies;
    float axiesMin;
    for (int i = 0; i < lines.size(); i++) {
        Vector2 l1 = lines[i];
        Vector2 l2 = lines[(i + 1) % lines.size()];
        Vector2 edge = Vector2Subtract(l2, l1);

        axies = Vector2Normalize({ -edge.y,edge.x });
        projectalVertices(lines, axies, &minA, &maxA);
        projectalCircle(v, radius, axies, &minB, &maxB);
        if (minA >= maxB || minB >= maxA)
            return false;
        axiesMin = fminf(maxB - minA, maxA - minB);
        if (axiesMin < dephtV)
        {
            dephtV = axiesMin;
            dirV = axies;
        }
    }
    int closest = closestPointToCricle(v, lines);
    Vector2 c = lines[closest];
    axies = Vector2Normalize(Vector2Subtract(c, v));
    projectalVertices(lines, axies, &minA, &maxA);
    projectalCircle(v, radius, axies, &minB, &maxB);
    if (minA >= maxB || minB >= maxA)
        return false;
    axiesMin = fminf(maxB - minA, maxA - minB);
    if (axiesMin < dephtV)
    {
        dephtV = axiesMin;
        dirV = axies;
    }
    Vector2 poliDir = Vector2Subtract(getCenter(lines), v);
    if (Vector2DotProduct(poliDir, dirV) < 0)
        dirV = { -dirV.x,-dirV.y };

    if (dir)
        *dir = dirV;
    if (depth)
        *depth = dephtV;
    return true;
}

bool CheckCollisionLines(std::vector<Vector2> lines1, std::vector<Vector2> lines2,Vector2* dir,float *depth) {

    if (lines1.size() <= 0 || lines2.size() <= 0)
        return false;
    Vector2 dirV = { 0,0 };
    float dephtV = std::numeric_limits<float>::max();
    for (int i = 0; i < lines1.size(); i++) {
        Vector2 l1 = lines1[i];
        Vector2 l2 = lines1[(i + 1) % lines1.size()];
        Vector2 edge = Vector2Subtract(l2, l1);
        float minA, maxA;
        float minB, maxB;
        Vector2 axies = Vector2Normalize({ -edge.y,edge.x });
        projectalVertices(lines1, axies, &minA, &maxA);
        projectalVertices(lines2, axies, &minB, &maxB);
        if (minA >= maxB || minB >= maxA)
            return false;
        float axiesMin = fminf(maxB - minA, maxA - minB);
        if (axiesMin < dephtV)
        {
            dephtV = axiesMin;
            dirV = axies;
        }

    }
    for (int i = 0; i < lines2.size(); i++) {
        Vector2 l1 = lines2[i];
        Vector2 l2 = lines2[(i + 1) % lines2.size()];
        Vector2 edge = Vector2Subtract(l2, l1);
        float minA, maxA;
        float minB, maxB;
        Vector2 axies = Vector2Normalize({ -edge.y,edge.x });
        projectalVertices(lines1, axies, &minB, &maxB);
        projectalVertices(lines2, axies, &minA, &maxA);
        if (minA >= maxB || minB >= maxA)
            return false;
        float axiesMin = fminf(maxB - minA, maxA - minB);
        if (axiesMin < dephtV)
        {
            dephtV = axiesMin;
            dirV = axies;
        }
    }

    Vector2 poliDir = Vector2Subtract(getCenter(lines1), getCenter(lines2));
    if (Vector2DotProduct(poliDir, dirV) < 0)
        dirV = { -dirV.x,-dirV.y };

    if (dir)
        *dir = dirV;
    if (depth)
        *depth = dephtV;
    return true;
}

#ifdef showColliders
#include "../GameObject.h"

void CollisionElement::draw(GameObject *obj) {
    Vector3 circle;
    std::vector<Vector2> points;
    switch (type) {

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
                DrawLineEx(p1, p2, 7, { 0,0,0,255 });
                DrawLineEx(p1, p2, 5, { 255,0,0,255 });
                DrawLineEx(p1, p2, 3, { 255,255,0,255 });
            }

            break;
    }
}
#endif
