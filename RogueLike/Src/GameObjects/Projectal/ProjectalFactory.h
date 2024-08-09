#pragma once
#include "Projectal.h"

class ProjectalFactory
{

public:

	static Projectal* getProjectal(int ID, Vector2 dir = { 0,0 });
};

