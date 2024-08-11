#pragma once
#include "raylib.hpp"
#include "../Font.h"
#include "ObjectType.h"
#include "../Core/Controller/TextureController.h"

class GameObject {
protected:
    Rectangle pos = { 0.0f,0.0f,64.0f,64.0f };
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

#pragma region Getters
    Vector2 getPosPoint() { return { pos.x, pos.y }; }

    Rectangle getPos() { return pos; }

    int getDrawOrder() { return drawOrder; }

    ObjectType getType() { return type; }

    virtual float getSpeed() { return 0.0f; }

    virtual float getAngle() { return 0.0f; }

    virtual Vector2 getRotationPoint() { return { 0.0f,0.0f }; }

    bool movingObject() { return moving; }

    virtual Vector2 getHoldPoint() { return { pos.x + pos.width / 2,pos.y + pos.width / 2 }; }

    virtual bool getIsUpdate() { return true; }
#pragma endregion Getters

#pragma region Setters
    virtual void setPos(Vector2 point) { pos.x = point.x; pos.y = point.y; }

    void setType(ObjectType type) { this->type = type; }
#pragma endregion Setters

    void move(Vector2 move) { pos.x += move.x; pos.y += move.y; }

    friend class Collider;
};
