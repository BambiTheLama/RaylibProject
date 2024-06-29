#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
class GameObject;
class Weapon
{
	GameObject* thisObj = nullptr;
	WeaponNodeTrigger weaponNodeTrigger;
protected:
	WeaponStats stats;
public:
	Weapon();

	void update();

	virtual void use(Vector2 dir, float deltaTime) = 0;

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	void setWeaponNodeTrigger(WeaponNodeTrigger trigger) { weaponNodeTrigger = trigger; }
private:
	void findThisObject();
};

