#pragma once
#include "raylib.h"

class ShadowObject
{
	int drawOrder = 0;
public:

	virtual void drawShadow() = 0;

	int getDrawOrder() { return drawOrder; }

	virtual Rectangle getShadowPos();
};

