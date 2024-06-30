#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"

class Explosion :
    public Projectal, public GameObject, public Collider
{
	float damage;
	float time;
	float timeMax;
	float range=1.0f;
	const float minRange = 1;
	Vector2 center;
public:
	Explosion();

	void update(float deltaTime);

	void draw();

	void dealDamage(Collider* collider);

	void onTrigger(Collider* collider) override;

	void onTriggerEnter(Collider* collider) override;

private:
	virtual void updateStatsAfterSetStats();
};

