#pragma once
#include "../GameObject.h"
#include "../Items/Item.h"

class ShopKeeper;
class ShopItem :
    public GameObject, public Interactive
{
    ShopKeeper* shopKeeper = nullptr;
    SoundController buySound;
    SoundController cancelSound;
    Item* item = nullptr;
    int price = 1000;
public:
    ShopItem(Rectangle pos, Item* item);

    ~ShopItem();

    void interact(GameObject* interactObject);

    void start();

    void draw();

    void draw(Rectangle pos, Color c);

    void setShopSkeeper(ShopKeeper* shopKeeper);

    void setPrice(int price) { this->price = price; }
};

