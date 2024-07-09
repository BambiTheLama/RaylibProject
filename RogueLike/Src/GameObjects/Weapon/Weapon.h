#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
#include "json.hpp"
#include <string>

class GameObject;
class Weapon
{
	GameObject* thisObj = nullptr;
	WeaponNodeTrigger weaponNodeTrigger;
protected:
	int weaponTier = 0;
	WeaponStats stats;
	static nlohmann::json weaponData;
	GameObject* owner;
public:
	Weapon(GameObject* owner = nullptr);

	void update();

	virtual void use(Vector2 dir, float deltaTime) = 0;

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	void setWeaponNodeTrigger(WeaponNodeTrigger trigger) { weaponNodeTrigger = trigger; }

	void setOwner(GameObject* owner) { this->owner = owner; }

	friend class GameScene;
private:
	void findThisObject();

	static void loadWeaponData(std::string weaponDataPath);
};

