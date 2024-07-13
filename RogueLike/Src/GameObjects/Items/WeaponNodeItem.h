#pragma once
#include "../Weapon/WeaponNode.h"

class WeaponNodeItem
{
	WeaponNode node;
public:
	void setWeaponNode(WeaponNode node) { this->node = node; }

	WeaponNode* getWeaponNode() { return &node; }
};

