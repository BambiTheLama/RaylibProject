#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
#include "json.hpp"
#include <string>
#include "../Items/WeaponNodeItem.h"

class Inventory;
class GameObject;
class Weapon
{
	Inventory* inventory;
	GameObject* thisObj = nullptr;
	WeaponNodeTrigger weaponNodeTrigger;
	std::vector<WeaponNodeItem*> weaponSlots;
protected:
	int weaponTier = 0;
	WeaponStats stats;
	static nlohmann::json weaponData;
public:
	Weapon();

	~Weapon();

	void update();

	void clickAtInventory();

	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; }

	virtual void use(Vector2 dir, float deltaTime) = 0;

	WeaponNodeItem* removeWeaponNodeItem(int n);

	void drawWeaponDescription(Rectangle pos, float textSize);

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	WeaponNodeItem* removeSlot(int slot);

	void drawWeaponNodeStats(Rectangle pos, float textSize, bool flexBox);

	bool addSlot(int slot, WeaponNodeItem* node);

	float getRange() { return stats.range; }

	static Rectangle getSlotPos(Rectangle pos, int slot = 0, int row = 0, Vector2 slotSize = { 64.0f,64.0f }, float itemSpaceing = 10.0f);

	friend class GameScene;
private:
	void findThisObject();

	static void loadWeaponData(std::string weaponDataPath);

	void updateWeaponNodesEfects();
protected:
	void setNumberOfSlots(int slots);

};

