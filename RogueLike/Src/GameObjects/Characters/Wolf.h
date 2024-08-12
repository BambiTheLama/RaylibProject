#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../../Core/Controller/AIController.h"
class Wolf :
    public GameObject,public Hitable,public Collider,public Character
{
    int target = 0b110;
    float damge = 1.0f;
    float attackTime = 0.0f;
    float attackTimeMax = 1.0f;
    float recoveryTime = 0;
    float recoveryTimeMax = 0.5;
    float speed = 200.0f;
    Vector2 attackDir = { 0.0f,0.0f };
    CharacterController controller;
    AIController* ai;
    Vector2 dir = { 0.0f,0.0f };
    bool col = false;
public:
    Wolf(float x,float y);

    void destroy();

    void update(float deltaTime);

    void draw();

    void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime);

    void onCollision(Collider* collider);

    void setPos(Vector2 point) { pos.x = point.x - pos.width / 2; pos.y = point.y - pos.height / 2; }

    void destoryController();

    void onHit();

    virtual float getSpeed() { return speed; }
};

