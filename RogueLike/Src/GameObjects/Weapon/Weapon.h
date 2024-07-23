#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
#include "json.hpp"
#include <string>
#include "../Items/WeaponNodeItem.h"
#include "../../Core/Controller/ShaderController.h"

class Inventory;
class GameObject;
class Weapon
{
	Inventory* inventory = nullptr;
	GameObject* thisObj = nullptr;
	WeaponStats difoltStats;
	WeaponNodeTrigger weaponNodeTrigger;
	std::vector<WeaponStats> weaponSlotsDifoltStat;
	std::vector<WeaponNodeItem*> weaponSlots;
	int cursorAt = -1;
protected:
	static nlohmann::json weaponData;
	int weaponTier = 0;
	float angle = 0.0f;
	Vector2 rotationPoint = { 0.0f,0.0f };
	WeaponStats stats;
	TextureController texture;
public:
	Weapon();

	~Weapon();

	void updateClick();

	void nextSlot();

	void privSlot();

	bool upSlot();

	bool downSlot();

	void takeItem();

	void resetSlot() { cursorAt = -1; }

	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; }

	virtual void use(Vector2 dir, float deltaTime) = 0;

	WeaponNodeItem* removeWeaponNodeItem(int n);

	void drawWeaponDescription(Rectangle pos, float textSize);

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

	WeaponNodeItem* removeSlot(int slot);

	void drawWeaponNodeStats(Rectangle pos, float textSize, bool flexBox);

	bool addSlot(int slot, WeaponNodeItem* node);

	float getRange() { return stats.range; }

	void setStats(WeaponStats ws) { difoltStats = ws; stats = ws; }

	static Rectangle getSlotPos(Rectangle pos, int slot = 0, int row = 0, Vector2 slotSize = { 64.0f,64.0f }, float itemSpaceing = 10.0f);

	static int getNumberOfSlotsInRow(float w, float size = 64.0f, float itemSpaceing = 10.0f);

	friend class GameScene;
private:
	void findThisObject();

	static void loadWeaponData(std::string weaponDataPath);

	void updateWeaponNodesEfects();
protected:
	void setNumberOfSlots(int slots);

	virtual void readFromWeaponData(std::string weaponType, int weaponTier = 0, int variant = 0);


};

