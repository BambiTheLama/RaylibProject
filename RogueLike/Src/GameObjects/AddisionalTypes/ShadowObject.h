#pragma once
#include "raylib.h"

class ShadowObject
{
	int drawOrder = 0;
public:

	virtual void drawShadow(){}

	int getDrawOrder() { return drawOrder; }

	virtual Rectangle getShadowPos();
};

