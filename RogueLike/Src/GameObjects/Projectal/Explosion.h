#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"

class Explosion :
    public Projectal, public GameObject, public Collider
{
	float damage = 1.0f;
	float time = 1.0f;
	float timeMax = 1.0f;
	float range = 1.0f;
	const float minRange = 1.0f;
	Vector2 center = { 0.0f,0.0f };
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

