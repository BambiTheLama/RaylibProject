#pragma once
#include "raylib.hpp"
#include "../GameObject.h"
#include "../AddisionalTypes/Interactive.h"

class Inventory;
class Weapon;
class Item :public Interactive
{
	Weapon* thisWeapon = nullptr;
	GameObject* thisObj = nullptr;
protected:
	Inventory* inventory = nullptr;
	GameObject* owner = nullptr;
	bool inInventory = false;
public:
#pragma region Constructor
	Item(){}

	virtual ~Item(){}
#pragma endregion Constructor
	void start();

	virtual void update(float deltaTime = 0.0f, Vector2 dir = { 0.0f,0.0f });

	virtual void use(Vector2 dir, float deltaTime){}

	virtual void stopUse(Vector2 dir, float deltaTime){}
	
	virtual void interact(GameObject* interactObject);

#pragma region DrawFun
	virtual void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) {}

	virtual void drawOverLine(Rectangle pos, Color OverLine, float overlineSize = 4);

	virtual void drawDescription(Rectangle pos, float textSize);
#pragma endregion DrawFun

#pragma region Getters
	GameObject* getThisObj();

	virtual bool canSwap() { return true; }
#pragma endregion Getters

#pragma region Setters
	virtual void setOwner(GameObject* owner) { this->owner = owner; inInventory = owner; setIsClosesObject(false);}

	virtual void setInventory(Inventory* inventory) { this->inventory = inventory; setIsClosesObject(false);}
#pragma endregion Setters

	friend class Inventory;
	friend class Weapon;
private:
};

