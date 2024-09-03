#include "ExplodeParticleSystem.h"
#include "../Game.h"
#include "raymath.h"

void ExplodeParticle::update(float deltaTime)
{
	size += deltaSize * deltaTime;
	speed += acceleration * deltaTime;
	timer -= deltaTime;
	angle += deltaTime * deltaAngle;
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

void ExplodeParticle::draw(TextureController& texture, float scale)
{
	if (timer <= 0.0f)
		return;
	int frame = texture.getFrames() * timer / timerMax;
	Rectangle drawPos = { pos.x,pos.y,size * scale ,size * scale };
	Color color = getColor();
	texture.draw(drawPos, false, false, frame, { drawPos.width / 2,drawPos.height / 2 }, angle, color);
	//DrawCircleV(pos, size, getColor()); 
}

ExplodeParticleSystem::ExplodeParticleSystem(Vector2 pos,float range, int particles, float timer, float speed)
{
	drawOrder = 10;
	this->pos = { pos.x - range,pos.y - range,range * 2,range * 2 };
	texture = TextureController("Projectal/Smoke.png");
	this->timer = 0.0f;
	for (int i = 0; i < particles; i++)
	{
		ExplodeParticle ep;
		Vector2 posV = Vector2Normalize({ (float)GetRandomValue(-100, 100) ,(float)GetRandomValue(-100, 100) });
		ep.pos.x = posV.x * GetRandomValue(0, range) + pos.x;
		ep.pos.y = posV.y * GetRandomValue(0, range) + pos.y;
		ep.dir.x = GetRandomValue(-100, 100) / 100.0f;
		ep.dir.y = GetRandomValue(-100, 100) / 100.0f;
		ep.dir = Vector2Normalize(ep.dir);
		ep.speed = GetRandomValue(-1 * speed, speed);
		ep.deltaAngle= GetRandomValue(-360, 360);
		ep.acceleration = -ep.speed / GetRandomValue(1, 100) / 30.0f;
		ep.timer = timer / 6.0f * 5.0f * GetRandomValue(1, 1000) / 1000.0f + timer / 6.0f;
		this->timer = fmaxf(this->timer, ep.timer);
		ep.size = GetRandomValue(100, 200);
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


