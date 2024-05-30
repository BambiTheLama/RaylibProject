#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../AddisionalTypes/Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
class AIController;
class Enemy :
    public GameObject, public Character, public Collider, public Hitable
{
    AIController* ai;
    CharacterController controller;
    float speed = 10;
public:
    Enemy(float x,float y);

    void update(float deltaTime);

    void draw();

    void move(Vector2 dir, float deltaTime);

    void action(Input input);

    void onCollisionEnter(Collider* collider);

    void destoryController();

    void onHit();
};

