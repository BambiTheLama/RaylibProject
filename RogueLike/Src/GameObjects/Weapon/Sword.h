#pragma once
#include "Weapon.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "WeaponStats.h"

class Sword:public GameObject,public Weapon,public Collider
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

	void update(float deltaTime);

	void draw();

	void use(Vector2 dir, float deltaTime);

	float getAngle() { return angle; }

	Vector2 getRotationPoint();

	void onTriggerEnter(Collider* collider);

	bool isUsing() { return useTime > 0; }

private:
	void updateWeaponSize();

	void readFromWeaponData(std::string weaponType, int variant, std::vector<Vector2>& col, std::string& texturePath);
};

