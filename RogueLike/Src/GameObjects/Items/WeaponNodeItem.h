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
#pragma region Constructor
	WeaponNodeItem();

	WeaponNodeItem(std::string path);

	WeaponNodeItem(nlohmann::json j);
#pragma endregion Constructor

	void update(float deltaTime);

#pragma region DrawFun
	void draw();

	void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) override;

	void drawDescription(Rectangle pos, float textSize) override;
#pragma endregion DrawFun

	void setWeaponNode(WeaponNode node) { this->node = node; }

	WeaponNode* getWeaponNode() { return &node; }

	void setOwner(GameObject* owner);

};

