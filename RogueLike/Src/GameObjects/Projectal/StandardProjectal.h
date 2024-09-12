#pragma once
#include "Projectal.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include <json.hpp>
#include "../AddisionalTypes/LightObject.h"

class StandardProjectal:public Projectal,public GameObject,public Collider
{
	float timer = 1.0f;
	float frameTimer = 0.0f;
	TextureController texture;
	bool wasParticleSpawned = true;
public:
	StandardProjectal();

	StandardProjectal(nlohmann::json data, std::string type);

	void start() override;

	void destroy() override;

	void update(float deltaTime);

	void draw();

	void onTriggerEnter(Collider* collider);

	float getAngle();

	Vector2 getRotationPoint() { return rotationPoint; }

	void setPos(Vector2 p)override { pos.x = p.x ; pos.y = p.y ; }

private:

	void readData(nlohmann::json data, std::string type);

	Color getColor();
};

