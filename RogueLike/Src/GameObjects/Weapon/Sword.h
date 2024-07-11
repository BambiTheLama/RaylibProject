#pragma once
#include "Weapon.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "WeaponStats.h"
#include "../Items/Item.h"


class Sword:public GameObject,public Weapon,public Collider,public Item
{
	Vector2 rotationPoint;
	WeaponStats stats;
	float angle;
	float reloadTime = 0.0f;
	float useTime = 0.0f;
	int numberOfUse = 0;
	bool used = false;
	bool left = false;
	TextureController texture;
public:
	Sword(GameObject* owner = nullptr, std::string weaponType = "", int variant = 0);

	~Sword() { printf("KURWA\n"); }

	void update(float deltaTime) override;

	void draw() override;

	void drawIcon(Rectangle pos) override;

	void drawDescription(Vector2 center, float wight) override;

	void use(Vector2 dir, float deltaTime) override;

	float getAngle() override { return angle; }

	Vector2 getRotationPoint();

	void onTriggerEnter(Collider* collider) override;

	bool isUsing() { return useTime > 0; }

	bool canSwap() override { return useTime <= 0.0f && reloadTime <= 0.0f; }

private:
	void updateWeaponSize();

	void readFromWeaponData(std::string weaponType, int variant, std::vector<Vector2>& col, std::string& texturePath);
};

