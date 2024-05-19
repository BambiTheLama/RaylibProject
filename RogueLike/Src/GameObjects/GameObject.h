#pragma once
#include "raylib.h"

enum class ObjectType :int
{
    NON    = 0b0000,
    Enemy  = 0b0001,
    Player = 0b0010,
    Wall   = 0b0100,
};

class GameObject {
protected:
    Rectangle pos;
    int drawOrder = 0;
    ObjectType type = ObjectType::NON;
public:
    virtual ~GameObject() {
    }

    virtual void update(float deltaTime) = 0;

    virtual void draw() = 0;

    Vector2 getPosPoint() { return {pos.x, pos.y}; }

    Rectangle getPos() { return pos; }

    int getDrawOrder() { return drawOrder; }

    ObjectType getType() { return type; }

    friend class Collider;
};

