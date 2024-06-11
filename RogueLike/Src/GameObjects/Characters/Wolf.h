#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../../Core/AIController.h"
class Wolf :
    public GameObject,public Hitable,public Collider,public Character
{
    int target = 0b110;
    float damge = 1;
    float attackTime = 0;
    float attackTimeMax = 2;
    float recoveryTime = 0;
    float recoveryTimeMax = 0.5;
    float speed = 0;
    Vector2 attackDir;
    CharacterController controller;
    AIController* ai;
    Vector2 dir;
    bool col = false;
public:
    Wolf(float x,float y);

    void destroy();

    void update(float deltaTime);

    void draw();

    void move(Vector2 dir, float deltaTime);

    void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime);

    void onCollision(Collider* collider);

    void setPos(Vector2 point) { pos.x = point.x - pos.width / 2; pos.y = point.y - pos.height / 2; }

    void destoryController();

    void onHit();

    virtual float getSpeed() { return speed; }
};

