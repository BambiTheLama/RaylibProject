#pragma once
#include "raylib.hpp"
class Item
{

public:
	Item(){}

	virtual ~Item(){}

	virtual void drawIcone(Rectangle pos){}

	virtual void use(Vector2 dir, float deltaTime){}

	virtual bool canSwap() { return true; }
};

