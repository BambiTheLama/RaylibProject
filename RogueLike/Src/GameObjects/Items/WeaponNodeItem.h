#pragma once
#include "../Weapon/WeaponNode.h"
#include "Item.h"
#include "../GameObject.h"
#include "../../Core/Controller/TextureController.h"
#include "../Collider/Collider.h"

class WeaponNodeItem
	:public Item, public GameObject, public Collider
{
	TextureController texture;
	WeaponNode node;
public:
	WeaponNodeItem();

	WeaponNodeItem(std::string path);

	WeaponNodeItem(nlohmann::json j);

	void setWeaponNode(WeaponNode node) { this->node = node; }

	WeaponNode* getWeaponNode() { return &node; }

	void update(float deltaTime);

	void setOwner(GameObject* owner);

	void draw();

	void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) override;

	void drawDescription(Rectangle pos, float textSize) override { node.drawNodeDescription(pos, textSize, true); }
};

