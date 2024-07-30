#include "ItemFactory.h"
#include "json.hpp"
#include <fstream>
#include "../Weapon/Sword.h"

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

Weapon* getWeapon(int variant, int tier, WeaponType wt)
{
	switch (wt)
	{
	case WeaponType::Axe:
		return new Sword(nullptr, "Axe", variant, weaponData, tier);
		break;
	case WeaponType::Sword:
		return new Sword(nullptr, "Sword", variant, weaponData, tier);
		break;
	case WeaponType::Pickaxe:
		return new Sword(nullptr, "Pickaxe", variant, weaponData, tier);
		break;
	case WeaponType::Bow:
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
