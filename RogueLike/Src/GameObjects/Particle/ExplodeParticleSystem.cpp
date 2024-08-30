#include "ExplodeParticleSystem.h"
#include "../Game.h"
#include "raymath.h"

void ExplodeParticle::update(float deltaTime)
{
	speed += acceleration * deltaTime;
	timer -= deltaTime;
	pos = Vector2Add(pos, Vector2Scale(dir, speed * deltaTime));
}

Color ExplodeParticle::getColor()
{
	if (colors.size() == 1)
		return colors[0];
	if (colors.size() > 1)
	{
		float procent = fabsf(timer / timerMax - 1.0f);
		int color = procent * colors.size();
		if (color + 1 >= colors.size() && color < colors.size())
		{
			return colors[color];
		}
		else
		{
			Color start = colors[color];
			Color end = colors[color + 1];
			return mixColor(start, end, color+1 - procent * colors.size());
		}

	}
	return WHITE;
}

void ExplodeParticle::draw()
{
	if (timer <= 0.0f)
		return;
	
	DrawCircleV(pos, size, getColor()); 
}

ExplodeParticleSystem::ExplodeParticleSystem(Rectangle pos, int particles, int timer)
{
	this->pos = pos;
	this->timer = timer;
	for (int i = 0; i < particles; i++)
	{
		ExplodeParticle ep;
		ep.pos.x = GetRandomValue(pos.x, pos.x + pos.width);
		ep.pos.y = GetRandomValue(pos.y, pos.y + pos.height);
		ep.dir.x = GetRandomValue(-100, 100) / 100.0f;
		ep.dir.y = GetRandomValue(-100, 100) / 100.0f;
		ep.speed = GetRandomValue(100, 300);
		ep.timer = timer;
		ep.size = GetRandomValue(10, 10);
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
		p.draw();
}


