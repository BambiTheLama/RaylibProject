#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
#include "json.hpp"
#include <string>
#include "../Items/WeaponNodeItem.h"
#include "../../Core/Controller/ShaderController.h"

enum class WeaponType {
	Axe = 0,
	Sword,
	Pickaxe,
	Bow,

	Size
};

WeaponType getRandomWeaponType();

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
#pragma region Constructor
	Weapon();

	~Weapon();
#pragma endregion Constructor

#pragma region Slots
	void updateClick();

	void nextSlot();

	void privSlot();

	bool upSlot();

	bool downSlot();

	void takeItem();

	WeaponNodeItem* removeSlot(int slot);

	void resetSlot() { cursorAt = -1; }
	
	bool addSlot(int slot, WeaponNodeItem* node);
	
	static Rectangle getSlotPos(Rectangle pos, int slot = 0, int row = 0, Vector2 slotSize = { 64.0f,64.0f }, float itemSpaceing = 10.0f);

private:
	void setNumberOfSlots(int slots);
public:
#pragma endregion Slots

	virtual void use(Vector2 dir, float deltaTime) = 0;

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

#pragma region DrawFun
	void drawWeaponDescription(Rectangle pos, float textSize);

	void drawWeaponNodeStats(Rectangle pos, float textSize, bool flexBox);
#pragma endregion DrawFun

#pragma region Setters
	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; }
	
	void setStats(WeaponStats ws) { difoltStats = ws; stats = ws; }
#pragma endregion Setters

#pragma region Getters
	float getRange() { return stats.range * stats.rangeMultiplier; }
	
	static int getNumberOfSlotsInRow(float w, float size = 64.0f, float itemSpaceing = 10.0f);
#pragma endregion Getters
	friend class GameScene;
private:
	void findThisObject();

	void updateWeaponNodesEfects();
#pragma region ReadFromFile
	static void loadWeaponData(std::string weaponDataPath);
protected:

	virtual void readFromWeaponData(std::string weaponType, int variant = 0);

	void readStats(nlohmann::json j, int variant = 0);
#pragma endregion RedFromFile
};

