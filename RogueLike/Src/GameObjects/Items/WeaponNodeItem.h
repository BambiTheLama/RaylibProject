#pragma once
#include "../Weapon/WeaponNode.h"
#include "Item.h"
#include "../GameObject.h"

class WeaponNodeItem
	:public Item, public GameObject
{
	WeaponNode node;
public:

	void setWeaponNode(WeaponNode node) { this->node = node; }

	WeaponNode* getWeaponNode() { return &node; }
};

