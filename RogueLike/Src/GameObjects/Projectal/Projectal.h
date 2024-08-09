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
	GameObject* owner;
	WeaponStats stats;
public:
	void setWeaponNodeTrigger(WeaponNodeTrigger trigger) { this->weaponNodeTrigger = trigger; }

	void setWeaponStats(WeaponStats stats) { this->stats = stats; updateStatsAfterSetStats(); }

	virtual void setDir(Vector2 dir) { this->dir = dir; }

	void setOwner(GameObject* owner) { this->owner = owner; }

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	virtual void update(){}

private:
	bool findThisObject();

	virtual void updateStatsAfterSetStats() {}
};

