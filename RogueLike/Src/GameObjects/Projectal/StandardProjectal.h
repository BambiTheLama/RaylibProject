#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"

class StandardProjectal:public Projectal,public GameObject,public Collider
{
	float range = 1.0f;
	float timer = 1.0f;
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

	void setPos(Vector2 p)override { pos.x = p.x - pos.width / 2; pos.y = p.y - pos.height / 2; }

private:
	virtual void updateStatsAfterSetStats();
};

