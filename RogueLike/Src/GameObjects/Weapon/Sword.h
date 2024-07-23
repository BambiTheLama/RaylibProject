#pragma once
#include "Weapon.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "WeaponStats.h"
#include "../Items/Item.h"



class Sword:public GameObject,public Weapon,public Collider,public Item
{
	float reloadTime = 0.0f;
	float useTime = 0.0f;
	int numberOfUse = 0;
	bool used = false;
	bool left = false;
	bool flipHorizontal = false;
public:
	Sword(GameObject* owner = nullptr, std::string weaponType = "", int variant = 0);

	~Sword() {  }

	void update(float deltaTime) override;

	void setInventory(Inventory* inventory) { Weapon::setInventory(inventory); Item::setInventory(inventory); }

	void draw() override;

	void drawIcon(Rectangle pos, bool onlyIcon = true) override;

	void drawDescription(Rectangle pos,float textSize) override;

	void use(Vector2 dir, float deltaTime) override;

	float getAngle() override { return angle; }

	Vector2 getRotationPoint();

	void onTriggerEnter(Collider* collider) override;

	bool isUsing() { return useTime > 0; }

	bool canSwap() override { return useTime <= 0.0f && reloadTime <= 0.0f; }

private:

	void updateWeaponSize();

protected:

	void readFromWeaponData(std::string weaponType, std::vector<Vector2>& col, int weaponTier = 0, int variant = 0);
};

