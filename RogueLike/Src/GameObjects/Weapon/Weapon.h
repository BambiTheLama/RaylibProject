#pragma once
#include "raylib.hpp"
class Weapon
{
public:
	virtual void use(Vector2 dir, float deltaTime) = 0;
};

