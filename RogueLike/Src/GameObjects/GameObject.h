#pragma once
#include "raylib.hpp"
#include "../Font.h"

enum class ObjectType :int
{
    NON        = 0b0000,
    Enemy      = 0b0001,
    Player     = 0b0010,
    Wall       = 0b0100,
    SpawnPoint = 0b1000
};

class GameObject {
protected:
    Rectangle pos;
    int drawOrder = 0;
    bool moving = true;
    ObjectType type = ObjectType::NON;
public:
    virtual ~GameObject() {
    }

    virtual void start(){}

    virtual void destroy(){}

    virtual void update(float deltaTime){}

    virtual void draw(){}

    Vector2 getPosPoint() { return {pos.x, pos.y}; }

    Rectangle getPos() { return pos; }

    virtual void setPos(Vector2 point) { pos.x = point.x; pos.y = point.y; }

    void move(Vector2 move) { pos.x += move.x; pos.y += move.y; }

    int getDrawOrder() { return drawOrder; }

    ObjectType getType() { return type; }

    void setType(ObjectType type) { this->type = type; }

    bool movingObject() { return moving; }

    virtual float getSpeed() { return 0; }

    virtual float getAngle() { return 0; }

    virtual Vector2 getRotationPoint() { return { 0,0 }; }

    friend class Collider;
};

