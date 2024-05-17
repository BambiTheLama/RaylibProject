#pragma once
#include <list>
#include <vector>

#include "raylib.h"
#define showColliders

enum class CollisionType {
    Line, Box, Circle
};

class GameObject;

class CollisionElement {
    CollisionType type;

public:
    CollisionElement(CollisionType type) { this->type = type; }

    CollisionType getType() { return type; }

    virtual bool isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement, Vector2 collisionElementPos) = 0;

    virtual Rectangle getBox(Vector2 pos) {
        return {0, 0, 0, 0};
    }

    virtual Vector3 getCircle(Vector2 pos) {
        return {0, 0};
    }

    virtual std::vector<Vector2> getLines(Vector2 pos) {
        return std::vector<Vector2>();
    }

#ifdef showColliders
    void draw(GameObject *obj);
#endif
};

bool CheckCollisionRecLine(Rectangle rec, Vector2 start, Vector2 end);

bool CheckCollisionCircles(Vector3 p1, Vector3 p2);

bool CheckCollisionCircleLine(Vector2 v, float radius, Vector2 p1, Vector2 p2);

bool CheckCollisionCircleLines(Vector2 v, float radius, std::vector<Vector2> points);

bool CheckCollisionLines(std::vector<Vector2> lines1, std::vector<Vector2> lines2);
