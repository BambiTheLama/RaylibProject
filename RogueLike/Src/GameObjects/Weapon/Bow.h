#pragma once
#include "../GameObject.h"
#include "Weapon.h"
#include "../Items/Item.h"

class Bow :
    public GameObject,public Weapon,public Item
{
    bool holdButton = false;
    bool startHoldButton = false;
    float angleDiff = 0.0f;
    float loadTime = 0.0f;
public:
    Bow(std::string weaponType = "", int variant = 0, nlohmann::json data = nlohmann::json(), int weaponTier = 0);

    void start();

    virtual void use(Vector2 dir, float deltaTime);

    virtual void stopUse(Vector2 dir, float deltaTime);
    
    void update(float deltaTime);

    void update(float deltaTime, Vector2 dir) override;

    void draw(Rectangle pos);

    void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) override;

    void draw();

    bool canSwap() { return loadTime <= 0.0f; }

    virtual float getUseTime() { return loadTime >= stats.getUseTime(); }

    bool isChargeWeapon()override { return true; }

    virtual bool stopUseWeapon() override { return loadTime >= stats.getUseTime(); }
protected:
    void readFromWeaponData(std::string weaponType, int variant);
};

