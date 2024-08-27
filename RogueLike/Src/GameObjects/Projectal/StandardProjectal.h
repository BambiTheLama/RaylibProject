#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include <json.hpp>

class StandardProjectal:public Projectal,public GameObject,public Collider
{
	float range = 1.0f;
	float rangeMax = 1.0f;
	float timer = 1.0f;
	int pirce = 1;
	int bounce = 1;
	float angle = 0.0f;
	float frameTimer = 0.0f;
	TextureController texture;
	Vector2 rotationPoint = { 0,0 };
public:
	StandardProjectal();

	StandardProjectal(nlohmann::json data, std::string type);

	void start() override;

	void destroy() override;

	void update(float deltaTime);

	void draw();

	void onTriggerEnter(Collider* collider);

	float getAngle() { return angle; }

	Vector2 getRotationPoint() { return rotationPoint; }

	void setPos(Vector2 p)override { pos.x = p.x ; pos.y = p.y ; }

private:
	virtual void updateStatsAfterSetStats();

	void readData(nlohmann::json data, std::string type);
};

