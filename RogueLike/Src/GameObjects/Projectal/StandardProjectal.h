#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"

class StandardProjectal:public Projectal,public GameObject,public Collider
{
	float range = 1.0f;
	int pirce = 1;
	int bounce = 1;
public:
	StandardProjectal();

	void start() override;

	void destroy() override;

	void update(float deltaTime);

	void draw();

	void onTriggerEnter(Collider* collider);

	float getAngle();

private:
	virtual void updateStatsAfterSetStats();
};

