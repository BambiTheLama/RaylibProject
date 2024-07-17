#pragma once
#include "../Weapon/WeaponNode.h"
#include "Item.h"
#include "../GameObject.h"
#include "../../Core/Controller/TextureController.h"

class WeaponNodeItem
	:public Item, public GameObject
{
	TextureController texture;
	WeaponNode node;
public:
	WeaponNodeItem(std::string path = " ");

	void setWeaponNode(WeaponNode node) { this->node = node; }

	WeaponNode* getWeaponNode() { return &node; }

	void drawIcon(Rectangle pos, bool onlyIcon = true) override;

	void drawNodeDescription(Rectangle pos, float textSize, bool flexBox) { node.drawNodeDescription(pos, textSize, flexBox); }
};

