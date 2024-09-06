#include "ExplodeParticleSystem.h"
#include "../Game.h"
#include "raymath.h"


ExplodeParticleSystem::ExplodeParticleSystem(Vector2 pos,float range, int particles, float timer, float speed)
{
	drawOrder = 10;
	this->pos = { pos.x - range,pos.y - range,range * 2,range * 2 };
	texture = TextureController("Projectal/Smoke.png");
	this->timer = 0.0f;
	for (int i = 0; i < particles; i++)
	{
		Particle ep;
		Vector2 posV = Vector2Normalize({ (float)GetRandomValue(-100, 100) ,(float)GetRandomValue(-100, 100) });
		ep.pos.x = posV.x * GetRandomValue(0, (int)range) + pos.x;
		ep.pos.y = posV.y * GetRandomValue(0, (int)range) + pos.y;
		ep.dir.x = GetRandomValue(-100, 100) / 100.0f;
		ep.dir.y = GetRandomValue(-100, 100) / 100.0f;
		ep.dir = Vector2Normalize(ep.dir);
		ep.speed = (float)GetRandomValue(-1 * (int)speed, (int)speed);
		ep.deltaAngle = (float)GetRandomValue(-360, 360);
		ep.acceleration = -ep.speed / GetRandomValue(1, 100) / 30.0f;
		ep.timer = timer / 6.0f * 5.0f * GetRandomValue(1, 1000) / 1000.0f + timer / 6.0f;
		this->timer = fmaxf(this->timer, ep.timer);
		ep.size = (float)GetRandomValue(100, 200);
		//ep.deltaSize = GetRandomValue(-100, -50);
		ep.timerMax = ep.timer;
		this->particles.push_back(ep);

	}
}

void ExplodeParticleSystem::update(float deltaTime)
{
	timer -= deltaTime;
	for (auto &p : particles)
		p.update(deltaTime);
	if (timer <= 0)
		Game::deleteObject(this);

}

void ExplodeParticleSystem::draw()
{
	for (auto p : particles)
		p.draw(texture);
}

void ExplodeParticleSystem::drawLight()
{
	BeginBlendMode(BLEND_ADD_COLORS);
	for (auto p : particles)
		p.draw(texture,2.0f);
	EndBlendMode();
}


