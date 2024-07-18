#pragma once
#include "raylib.hpp"
#include "../GameObject.h"

class Inventory;
class Item
{
	GameObject* thisObj = nullptr;
protected:
	Inventory* inventory;
	GameObject* owner = nullptr;
	static bool showDescriptions;
public:
	Item(){}

	virtual ~Item(){}

	void setOwner(GameObject* owner) { this->owner = owner; }

	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; }

	virtual void update(float deltaTime);

	virtual void drawIcon(Rectangle pos, bool onlyIcon = true) {}

	virtual void drawDescription(Rectangle pos, float textSize){}

	virtual void use(Vector2 dir, float deltaTime){}

	virtual bool canSwap() { return true; }

	static void swapVisibleDescriptions() { showDescriptions = !showDescriptions; }

	friend class Inventory;
	friend class Weapon;
private:

	void findThisObject();
};

