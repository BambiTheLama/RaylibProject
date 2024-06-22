#pragma once
#include <iostream>
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Weapon/Sword.h"

class Player : public GameObject, public Character, public Collider,public Hitable {
    float speed = 600;
    Weapon* weapon;
public:
    Player(float x,float y);

    ~Player();

    void start() override;

    void update(float deltaTime) override;

    void move(Vector2 dir, float deltaTime);

    void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime);

    void draw();

    void setPos(Vector2 point) { pos.x = point.x - pos.width / 2; pos.y = point.y - pos.height / 2; }

    void onCollisionEnter(Collider* collider) override;

    void onCollisionExit(Collider* collider) override;

    virtual float getSpeed() { return speed; }

};
