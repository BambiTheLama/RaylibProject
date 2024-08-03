#pragma once
#include <list>
#include <vector>
#include "raylib.hpp"

#define showColliders

enum class CollisionType {
    Line, Circle
};

class GameObject;

class CollisionElement {
    CollisionType type;

public:
    CollisionElement(CollisionType type) { this->type = type; }

    virtual void update(GameObject* gm,bool mirror){}

    virtual bool isCollidiongWith(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos, Vector2* dir, float* depht) = 0;

    Vector2 getCollisionVectorDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos);

    virtual void flipHorizontalElement(float size){}

    virtual void scaleElement(float scale){}

#pragma region Getters
    CollisionType getType() { return type; }

    virtual Vector3 getCircle(Vector2 pos) {return { 0, 0,0 };}

    virtual std::vector<Vector2> getLines(Vector2 pos) { return std::vector<Vector2>(); }

    virtual Vector2 getMinPos() { return{ 0.0f,0.0f }; }

    Vector2 getRotationPoint() { return{ 0.0f,0.0f }; };

    virtual Vector2 getMaxPos() { return{ 0.0f,0.0f }; }
#pragma endregion Getters

#ifdef showColliders
    void draw(GameObject *obj);
#endif
};
bool CheckCollisionCircles(Vector3 p1, Vector3 p2, Vector2* dir, float* depth);

bool CheckCollisionCircleLines(Vector2 v, float radius, std::vector<Vector2> points, Vector2* dir, float* depth);

bool CheckCollisionLines(std::vector<Vector2> lines1, std::vector<Vector2> lines2, Vector2* dir, float* depth);

