#pragma once
#include <list>
#include <vector>
#include "raylib.hpp"

#define showColliders

enum class CollisionType {
    Line, Circle
};

class GameObject;
extern enum class Dir :char;
class CollisionElement {
    CollisionType type;

public:
    CollisionElement(CollisionType type) { this->type = type; }

    virtual void update(GameObject* gm){}

    CollisionType getType() { return type; }

    virtual bool isCollidiongWith(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos, Vector2* dir, float* depht) = 0;

    Vector2 getCollisionVectorDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos);

    virtual Vector3 getCircle(Vector2 pos) {
        return { 0, 0,0 };
    }

    virtual std::vector<Vector2> getLines(Vector2 pos) {
        return std::vector<Vector2>();
    }



#ifdef showColliders
    void draw(GameObject *obj);
#endif
};

bool CheckCollisionRecLine(Rectangle rec, Vector2 start, Vector2 end);

Dir CheckCollisionRecLineDir(Rectangle rec, Vector2 start, Vector2 end);

bool CheckCollisionCircles(Vector3 p1, Vector3 p2);

bool CheckCollisionCircleLine(Vector2 v, float radius, Vector2 p1, Vector2 p2);

bool CheckCollisionCircleLines(Vector2 v, float radius, std::vector<Vector2> points, Vector2* dir, float* depth);

bool CheckCollisionLines(std::vector<Vector2> lines1, std::vector<Vector2> lines2, Vector2* dir, float* depth);

