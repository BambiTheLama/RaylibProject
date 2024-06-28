#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"

class StandardProjectal:public Projectal,public GameObject,public Collider
{
	float time = 1;
	int pirce = 1;
public:
	StandardProjectal();

	virtual void setWeaponStats(WeaponStats stats) { Projectal::setWeaponStats(stats); time = stats.useTime; pirce = stats.countOfUse; }

	void update(float deltaTime);

	void draw();

	void onTriggerEnter(Collider* collider);

	float getAngle();
	
};

