#pragma once
#include <iostream>
#include "GameObject.h"
#include "AddisionalTypes/Character.h"
#include "AddisionalTypes/Collider/Collider.h"


class Player : public GameObject, public Character, public Collider {
    float speed = 100;

public:
    Player(int x = 0, int y = 0);

    ~Player();

    void update(float deltaTime);

    void move(Vector2 dir, float deltaTime);

    void action(Input input);

    void draw();

    void onCollisionEnter(Collider *collider) override { printf("KURWA\n"); }

    void onCollisionExit(Collider *collider) override { printf("KURWA END\n"); }
};
