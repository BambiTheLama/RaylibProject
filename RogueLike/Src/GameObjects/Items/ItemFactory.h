#pragma once
#include "../GameObject.h"
#include "WeaponNodeItem.h"
#include "../Weapon/Weapon.h"
#include "Item.h"
#include <string>

void setFactoryItemSeed(int seed);

void setUpItemFactory(std::string path);

WeaponNodeItem* getWeaponNode(int tier);

Weapon* getWeapon(int variant,int tier, WeaponType wt);

Item* getItem(int tier);
