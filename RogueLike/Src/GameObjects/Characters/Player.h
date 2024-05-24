#pragma once
#include <iostream>
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"


class Player : public GameObject, public Character, public Collider,public Hitable {
    float speed = 500;

public:
    Player(int x = 0, int y = 0);

    ~Player();

    void update(float deltaTime) override;

    void move(Vector2 dir, float deltaTime);

    void action(Input input, Vector2 dir,float deltaTime);

    void draw();

    void onCollisionEnter(Collider* collider) override;

    void onCollisionExit(Collider* collider) override;

    virtual float getSpeed() { return speed; }

};
