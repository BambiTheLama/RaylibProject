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
	WeaponStats stats;
	static nlohmann::json weaponData;
public:
	Weapon();

	void update();

	virtual void use(Vector2 dir, float deltaTime) = 0;

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	void setWeaponNodeTrigger(WeaponNodeTrigger trigger) { weaponNodeTrigger = trigger; }

	friend class GameScene;
private:
	void findThisObject();

	static void loadWeaponData(std::string weaponDataPath);
};

