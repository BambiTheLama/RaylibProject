#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
#include "json.hpp"
#include <string>
#include "../Items/WeaponNodeItem.h"


class GameObject;
class Weapon
{
	GameObject* thisObj = nullptr;
	WeaponNodeTrigger weaponNodeTrigger;
	std::vector<WeaponNodeItem*> weaponSlots;
protected:
	int weaponTier = 0;
	WeaponStats stats;
	static nlohmann::json weaponData;
public:
	Weapon();

	void update();

	virtual void use(Vector2 dir, float deltaTime) = 0;

	void drawWeaponDescription(Rectangle pos, float textSize);

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	WeaponNodeItem* removeSlot(int slot);

	bool addSlot(int slot, WeaponNodeItem* node);

	float getRange() { return stats.range; }

	friend class GameScene;
private:
	void findThisObject();

	static void loadWeaponData(std::string weaponDataPath);

	void updateWeaponNodesEfects();
protected:
	void setNumberOfSlots(int slots);

};

