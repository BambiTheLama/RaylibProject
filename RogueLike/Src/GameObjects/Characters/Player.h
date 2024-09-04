#pragma once
#include <iostream>
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Weapon/Sword.h"
#include "../Items/Inventory.h"
#include "../AddisionalTypes/DrawUI.h"
#include "../../Core/Controller/ShaderController.h"
#include "../AddisionalTypes/Interactive.h"
#include "../AddisionalTypes/LightObject.h"

class Player 
    : public GameObject, public Character, public Collider,public Hitable,public DrawUI ,public LightObject
{
    float speed = 2;
    Inventory inventory;
    Vector2 useDir = { 0.0f,0.0f };
    Interactive* closeObj = nullptr;
    float timer=0.0f;
    int target = 0b010001;
public:
    Player(float x,float y);

    ~Player();

    void start() override;

    void update(float deltaTime) override;

    void updateCloseInteractive();

    void move(Vector2 dir, float deltaTime) override;

    void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime) override;

    void draw() override;

    void drawUI() override;

    void setPos(Vector2 point) { pos.x = point.x - pos.width / 2; pos.y = point.y - pos.height / 2; }

    void onCollisionEnter(Collider* collider) override;

    bool addItem(Item* i) { return inventory.addItem(i); }

    void onCollisionExit(Collider* collider) override;

    virtual float getSpeed() { return speed; }

    void interact();

    Interactive* getCloseInteractiveObjects();

};
