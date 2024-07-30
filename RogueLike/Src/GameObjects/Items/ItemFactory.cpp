#include "ItemFactory.h"
#include "json.hpp"
#include <fstream>

static nlohmann::json weaponData;
static nlohmann::json weaponNodeData;
static nlohmann::json itemData;

nlohmann::json readJson(std::string path)
{
	std::ifstream reader(path);
	nlohmann::json j;
	if (!reader.is_open())
		return j;
	reader >> j;
	return j;
}

void setUpItemFactory(std::string path)
{
	weaponData = readJson(path + "WeaponData.json");
	weaponNodeData = readJson(path + "WeaponNodeData.json");
	itemData = readJson(path + "ItemData.json");
}

WeaponNodeItem* getWeaponNode(int tier, WeaponNodeType type)
{
	return nullptr;
}

Weapon* getWeapon(int tier, WeaponType wt)
{
	return nullptr;
}

Item* getItem(int tier)
{
	return nullptr;
}
