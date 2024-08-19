#pragma once
#include "raylib.hpp"
#include <vector>
#include "WeaponNodeTrigger.h"
#include "json.hpp"
#include <string>
#include "../Items/WeaponNodeItem.h"
#include "../../Core/Controller/ShaderController.h"
#include "../Projectal/ProjectalID.h"

enum class WeaponType {
	Axe = 0,
	Book,
	Bow,
	Dager,
	DagerSai,
	Hamer,
	Shuriken,
	Sicle,
	Spear,
	Sword,
	Staf,
	Wand,
};

WeaponType getRandomWeaponType();

class Inventory;
class GameObject;
class Item;

class Weapon
{
	GameObject* thisObj = nullptr;
	Item* thisItem = nullptr;
	WeaponStats difoltStats;
	WeaponNodeTrigger weaponNodeTrigger;
	std::vector<WeaponStats> weaponSlotsDifoltStat;
	std::vector<WeaponNodeItem*> weaponSlots;
	int cursorAt = -1;
	bool spawn = false;
	std::string spawnName = "";
	ProjectalID spawnID = ProjectalID::Arrow;
protected:
	static nlohmann::json weaponData;
	bool mirror = false;
	int weaponTier = 0;
	float angle = 0.0f;
	Vector2 rotationPoint = { 0.0f,0.0f };
	Vector2 rotationPointStart = { 0.0f,0.0f };
	Vector2 rotationPointEnd = { 0.0f,0.0f };
	Vector2 spawnPoint = { 0.0f,0.0f };
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

	void start();

	virtual void use(Vector2 dir, float deltaTime) = 0;

	virtual void stopUse(Vector2 dir,float deltaTime){}

	bool triggerNode(WeaponNodeActivation activation, WeaponStats stats);

#pragma region DrawFun
	void drawWeaponPoints();

	void drawWeaponDescription(Rectangle pos, float textSize);

	void drawWeaponNodeStats(Rectangle pos, float textSize, bool flexBox);
#pragma endregion DrawFun

#pragma region Setters
	void scaleWeapon(float scale);
	
	void setStats(WeaponStats ws) { difoltStats = ws; stats = ws; }
#pragma endregion Setters

#pragma region Getters
	float getRange() { return stats.range * stats.rangeMultiplier; }

	float getAngle() { return angle; }

	GameObject* getThisGameObject();

	Vector2 getSpawnPoint();

	bool isSpawningProjectal() { return spawn; }
	
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

	void setIsSpawn(bool spawn) { this->spawn = spawn; updateWeaponNodesEfects(); }

	void setSpawnID(ProjectalID spawnID) { this->spawnID = spawnID; updateWeaponNodesEfects(); }
#pragma endregion RedFromFile
};

