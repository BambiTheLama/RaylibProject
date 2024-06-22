#pragma once
#include "../Weapon/WeaponNodeTrigger.h"
#include "raylib.hpp"

class GameObject;
class Projectal
{

	WeaponNodeTrigger weaponNodeTrigger;
	GameObject *thisObj = nullptr;
protected:
	Vector2 dir = { 1.0f,0.0f };
	WeaponStats stats;
public:
	void setWeaponNodeTrigger(WeaponNodeTrigger trigger) { this->weaponNodeTrigger = trigger; }

	virtual void setWeaponStats(WeaponStats stats) { this->stats = stats; }

	void setDir(Vector2 dir) { this->dir = dir; }

	bool triggerNode(WeaponNodeActivation activation);

	virtual void update(){}

private:
	bool findThisObject();
};

