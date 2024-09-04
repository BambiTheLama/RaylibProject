#pragma once
#include "raylib.h"
#include <list>

struct ShadowGeometry {
	Vector2 vertices[4];
};

class LightObject
{
	float radius = 0.0f;
protected:
	float zoom = 10.0f;
	bool valid = false;
	float timer = 0.0f;
	float lightTimer = 0.0f;
	float updateTimer = 0.1f;
	Vector2 lightPos = { 0,0 };
	Color colorCenter = WHITE;
	Color colorEnd = BLACK;
	std::list<ShadowGeometry> lightFan;
	RenderTexture2D lightTexture;
public:
	LightObject(float updateTimer=1.0f);

	virtual ~LightObject();

	void update(float deltaTime);

	virtual void drawLight();

	void setRange(float range);

private:
	void generateTexture();

	bool createLightFan();

	void computeShadowVolumeForEdge(Vector2 sp, Vector2 ep);
};

