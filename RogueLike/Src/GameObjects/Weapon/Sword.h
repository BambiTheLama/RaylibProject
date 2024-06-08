#pragma once
#include "Weapon.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
class Sword:public GameObject,public Weapon,public Collider
{
	Vector2 rotationPoint;
	float angle;
	GameObject* owner;
public:
	Sword(GameObject* owner);

	void update(float deltaTime);

	void draw();

	void use(Vector2 dir, float deltaTime);

	float getAngle() { return angle; }

	Vector2 getRotationPoint() { return rotationPoint; }

	void onTriggerEnter(Collider* collider);
};

