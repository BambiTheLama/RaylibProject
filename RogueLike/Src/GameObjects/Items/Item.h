#pragma once
#include "raylib.hpp"
#include "../GameObject.h"

class Item
{
	GameObject* thisObj = nullptr;
protected:
	GameObject* owner;
public:
	Item(){}

	virtual ~Item(){}

	void setOwner(GameObject* owner) { this->owner = owner; }

	void update();

	virtual void drawIcon(Rectangle pos){}

	virtual void drawDescription(Vector2 center,float wight){}

	virtual void use(Vector2 dir, float deltaTime){}

	virtual bool canSwap() { return true; }

private:

	void findThisObject();
};

