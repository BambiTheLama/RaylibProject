#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"

class Coin :
    public GameObject,public Collider
{
    TextureController texture;
    bool particleAcctivated = true;
    int coins;
public:
    Coin(Rectangle pos, int coins = 1);

    void start() override;

    void destroy()override;

    void update(float deltaTime) override;

    void draw() override;

    int getCoins() { return coins; }
};

