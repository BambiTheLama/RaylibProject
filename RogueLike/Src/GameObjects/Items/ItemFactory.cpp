#include "ItemFactory.h"
#include "json.hpp"
#include <fstream>
#include "../Weapon/Sword.h"
#include "../Weapon/Bow.h"
#include <magic_enum/magic_enum.hpp>

static nlohmann::json weaponData;
static nlohmann::json weaponNodeData;
static nlohmann::json itemData;

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

#define ENUM_TO_STRING(ENUM) #ENUM

Weapon* getWeapon(int variant, int tier, WeaponType wt)
{
	auto enumWeapon = magic_enum::enum_name(wt);
	const char* name = enumWeapon.data();
	switch (wt)
	{
	case WeaponType::Axe:
	case WeaponType::Dager:
	case WeaponType::DagerSai:
	case WeaponType::Hamer:
	case WeaponType::Shuriken:
	case WeaponType::Sicle:
	case WeaponType::Spear:
	case WeaponType::Sword:
		return new Sword(name, variant, weaponData, tier);
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
