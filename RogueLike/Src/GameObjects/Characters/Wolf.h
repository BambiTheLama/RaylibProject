#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../AddisionalTypes/Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../../Core/AIController.h"
class Wolf :
    public GameObject,public Hitable,public Collider,public Character
{
    int target = 0b110;
    float damge = 1;
    float attackTime = 0;
    float attackTimeMax = 2;
    Vector2 attackDir;
    CharacterController controller;
    AIController* ai;
public:
    Wolf(int x = 0, int y = 0);

    void update(float deltaTime);

    void draw();

    void move(Vector2 dir, float deltaTime);

    void action(Input input);

    void onCollisionEnter(Collider* collider);

    void destoryController();

    void onHit();
};

