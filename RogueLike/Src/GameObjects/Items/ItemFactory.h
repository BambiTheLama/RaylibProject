#pragma once
#include "../GameObject.h"
#include "WeaponNodeItem.h"
#include "../Weapon/Weapon.h"
#include "Item.h"
#include <string>

void setUpItemFactory(std::string path);

WeaponNodeItem* getWeaponNode(int tier, WeaponNodeType type);

Weapon* getWeapon(int variant,int tier, WeaponType wt);

Item* getItem(int tier);
