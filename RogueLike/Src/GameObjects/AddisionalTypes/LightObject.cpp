#include "LightObject.h"
#include "../GameObject.h"
#include <math.h>
#include "rlgl.h"

void LightObject::update(float deltaTime)
{
	timer += deltaTime * 5.f;
}

void LightObject::drawLight()
{
	GameObject* gm = dynamic_cast<GameObject*>(this);
	if (!gm)
		return;
	Vector2 pos = getMidlePoint(gm->getPos());
	//BeginBlendMode(BLEND_ADD_COLORS);
	BeginBlendMode(BLEND_CUSTOM);
	rlSetBlendFactors(0xffffffff, 0xffffffff, RL_MAX);

	float r = fmaxf(radius + (  50) * std::sin(timer), 0.0f);

	DrawCircleGradient(pos.x, pos.y, r, colorCenter, colorEnd);
	EndBlendMode();
}
