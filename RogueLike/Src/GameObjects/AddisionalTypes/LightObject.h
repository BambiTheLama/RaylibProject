#pragma once
#include "raylib.h"

class LightObject
{
protected:
	float radius = 600.0f;
	float timer = 0.0f;
	Color colorCenter = WHITE;
	Color colorEnd = BLANK;
public:
	void update(float deltaTime);

	virtual void drawLight();
};

