#include "FierParticle.h"
#include "raymath.h"

FierParticle::FierParticle(Vector2 pos)
{
	this->pos = { pos.x,pos.y,2,2 };
	for (int i = 0; i < 16; i++)
	{
		Particle p;
		resetParticle(p);
		particle.push_back(p);
	}
	texture = TextureController("Projectal/Smoke.png");
}

void FierParticle::update(float deltaTime)
{
	for (auto& p : particle)
	{
		p.update(deltaTime);
		if (p.timer <= 0)
			resetParticle(p);
	}

}

void FierParticle::draw()
{
	for (auto p : particle)
		p.draw(texture);
}

void FierParticle::resetParticle(Particle& p)
{
	const float timer = 2.5f;
	const int speed = 60;
	p.pos.x = pos.x + GetRandomValue(-(int)pos.width, (int)pos.width);
	p.pos.y = pos.y + GetRandomValue(-(int)pos.height, (int)pos.height);
	p.dir.x = GetRandomValue(-100, 100) / 100.0f;
	p.dir.y = -GetRandomValue(100, 1000) / 100.0f;
	p.dir = Vector2Normalize(p.dir);
	p.speed = (float)GetRandomValue(speed / 3, speed);
	p.deltaAngle = (float)GetRandomValue(-360, 360);
	p.acceleration = -p.speed / GetRandomValue(1, 100) / 30.0f;
	p.timer = timer / 3.0f * 2.0f * GetRandomValue(1, 1000) / 1000.0f + timer / 3.0f;
	p.timerMax = p.timer;
	p.size = (float)GetRandomValue(10, 20);
}
