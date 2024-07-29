#pragma once
#include "raylib.hpp"
#include "../GameObject.h"
#include "../AddisionalTypes/Interactive.h"

class Inventory;
class Item :public Interactive
{
	GameObject* thisObj = nullptr;
protected:
	Inventory* inventory = nullptr;
	GameObject* owner = nullptr;
	bool inInventory = false;
public:
	Item(){}

	virtual ~Item(){}

	virtual void setOwner(GameObject* owner) { this->owner = owner; inInventory = owner; setIsClosesObject(false);}

	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; setIsClosesObject(false);}

	virtual void update(float deltaTime);

	virtual void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) {}

	void drawOverLine(Rectangle pos, Color OverLine);

	virtual void interact(GameObject* interactObject);

	virtual void drawDescription(Rectangle pos, float textSize){}

	virtual void use(Vector2 dir, float deltaTime){}

	virtual bool canSwap() { return true; }

	GameObject* getThisObj();

	friend class Inventory;
	friend class Weapon;
private:
};

