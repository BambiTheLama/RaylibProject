#pragma once
#include "../Weapon/WeaponNodeTrigger.h"
#include "raylib.hpp"
#include "ProjectalID.h"
#include <json.hpp>

class GameObject;
class Projectal
{
	WeaponNodeTrigger weaponNodeTrigger;
	GameObject *thisObj = nullptr;
protected:
	float range = 1.0f;
	float rangeMax = 1.0f;
	int pirce = 1;
	int bounce = 1;
	float angle = 0.0f;
	float speed = 1.0f;
	Vector2 rotationPoint = { 0,0 };
	int target = 0;
	Vector2 dir = { 1.0f,0.0f };
	float rotationDiff = 0.0f;
	GameObject* owner;
	WeaponStats stats;
public:
	void setWeaponNodeTrigger(WeaponNodeTrigger trigger) { this->weaponNodeTrigger = trigger; }

	void setWeaponStats(WeaponStats stats) { this->stats = stats; }

	virtual void start();

	virtual void setDir(Vector2 dir);

	void setOwner(GameObject* owner) { this->owner = owner; }

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	virtual void update(){}

	void setTarget(int target) { this->target = target; }

	GameObject* getProjectalOwner() { return owner; }

	int getTarger() { return target; }

private:
	bool findThisObject();
};

