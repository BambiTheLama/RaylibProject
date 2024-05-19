#pragma once
#include "GameObject.h"
#include "AddisionalTypes/Character.h"
#include "AddisionalTypes/CharacterController.h"
#include "AddisionalTypes/Collider/Collider.h"
class AIController;
class Enemy :
    public GameObject,public Character,public Collider
{
    AIController* ai;
    CharacterController controller;
public:
    Enemy(int x = 0, int y = 0);

    void update(float deltaTime);

    void draw();

    void move(Vector2 dir, float deltaTime);

    void action(Input input);

    void onCollisionEnter(Collider* collider);
};

