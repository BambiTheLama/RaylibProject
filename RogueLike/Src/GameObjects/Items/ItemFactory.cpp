#include "ItemFactory.h"
#include "json.hpp"
#include <fstream>
#include "../Weapon/Sword.h"
#include "../Weapon/Bow.h"

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

WeaponNodeItem* getWeaponNode(int tier)
{
	if (weaponNodeData.size() <= 0)
		return nullptr;
	if (tier >= weaponNodeData.size())
		tier = weaponNodeData.size() - 1;

	if (weaponNodeData[tier].size() <= 0)
		return nullptr;
	int itemInTier = rand() % weaponNodeData[tier].size();
	return new WeaponNodeItem(weaponNodeData[tier][itemInTier]);
}

Weapon* getWeapon(int variant, int tier, WeaponType wt)
{
	switch (wt)
	{
	case WeaponType::Axe:
		return new Sword("Axe", variant, weaponData, tier);
		break;
	case WeaponType::Sword:
		return new Sword("Sword", variant, weaponData, tier);
		break;
	case WeaponType::Spear:
		return new Sword("Spear", variant, weaponData, tier);
		break;
	case WeaponType::Bow:
		return new Bow("Bow", variant, weaponData, tier);
		break;
	default:
		break;
	}
	return nullptr;
}

Item* getItem(int tier)
{
	return nullptr;
}
