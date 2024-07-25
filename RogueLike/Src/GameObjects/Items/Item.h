#pragma once
#include "raylib.hpp"
#include "../GameObject.h"

class Inventory;
class Item
{
	GameObject* thisObj = nullptr;
protected:
	Inventory* inventory = nullptr;
	GameObject* owner = nullptr;
	bool inInventory = false;
	bool closeItem = false;
public:
	Item(){}

	virtual ~Item(){}

	virtual void setOwner(GameObject* owner) { this->owner = owner; inInventory = owner; closeItem = false;}

	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; closeItem = false;}

	virtual void update(float deltaTime);

	virtual void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) {}

	virtual void drawDescription(Rectangle pos, float textSize){}

	virtual void use(Vector2 dir, float deltaTime){}

	virtual bool canSwap() { return true; }

	void setIsClose(bool close) { closeItem = close; }

	friend class Inventory;
	friend class Weapon;
private:

	void findThisObject();
};

