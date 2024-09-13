#pragma once
#include "../GameObject.h"
#include "WeaponNodeItem.h"
#include "../Weapon/Weapon.h"
#include "Item.h"
#include <string>

void setUpItemFactory(std::string path);

int getWeaponNodeSize(int tier);

int getWeaponSize();

int getWeaponVariantsSize(WeaponType wt);

WeaponNodeItem* getWeaponNode(int ID, int tier);

Weapon* getWeapon(int variant,int tier, WeaponType wt);

Item* getItem(int tier);
