#pragma once
#include "raylib.hpp"
#include "../Font.h"
#include "ObjectType.h"
#include "../Core/Controller/TextureController.h"

class GameObject {
protected:
    Rectangle pos = { 0.0f,0.0f,1.0f,1.0f };
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

    virtual float getSpeed() { return 0.0f; }

    virtual float getAngle() { return 0.0f; }

    virtual Vector2 getRotationPoint() { return { 0.0f,0.0f }; }

    friend class Collider;
};

