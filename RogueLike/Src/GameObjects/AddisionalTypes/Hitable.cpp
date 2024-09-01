#include "Hitable.h"
#include "../Game.h"
#include "../Particle/ParticleText.h"
#include <string>
#include "raymath.h"


int Hitable::showParticle = 0b1111101111;

Hitable::Hitable(float hp)
{
	setMaxHp(hp);
}

void Hitable::setMaxHp(float maxHp)
{
	float procent = this->hp / this->maxHp;
	this->maxHp = maxHp;
	this->hp = procent * maxHp;
	lastHp = hp;
}

bool Hitable::dealDamage(float damage, float invisibleFrames)
{
	if (this->invisibleFrames > 0.0f)
		return false;
	hitTimer = hitTimerMax;
	hp -= damage;

	deltaHp = (lastHp - hp) / hitTimer;
	this->invisibleFrames = invisibleFrames;
	onHit();
	GameObject* gm = dynamic_cast<GameObject*>(this);
	if (gm && ((int)gm->getType() & showParticle) != 0)
	{
		if (damage >= 0.1)
		{
			Rectangle pos = gm->getPos();
			std::string text = "{Icon:0}"+std::to_string(damage);
			text.erase(text.size() - 5, 5);
			Game::addObject(new ParticleText(pos.x + pos.width / 2, pos.y + pos.height / 2, 1, text));
		}

	}

	return true;
}

void Hitable::update(float deltaTime)
{
	if (invisibleFrames > 0)
		invisibleFrames -= deltaTime;
	if (hitTimer > 0.0f)
	{
		lastHp -= deltaHp * deltaTime;
		hitTimer -= deltaTime;
	}
	else
		lastHp = hp;
	if (lastHp <= 0)
	{
		deadTrigger();
	}
}

void Hitable::deadTrigger()
{
	Game::deleteObject(dynamic_cast<GameObject*>(this));
}

void Hitable::draw(Rectangle pos) {
	DrawRectangleRec(pos, GRAY);
	DrawRectangleRec({ pos.x, pos.y, pos.width * getAnimateHp(), pos.height }, GREEN);
	//DrawRectangleRec({ pos.x, pos.y, pos.width * getProcentHp(), pos.height }, RED);
	DrawRectangleLinesEx(pos, 3, BLACK);
}

Color Hitable::getHitColor(Color c)
{
	return mixColor(hitColor, c, Clamp(hitTimer / hitTimerMax, 0.0f, 1.0f));
}
