#include "Hitable.h"
#include "../Game.h"

Hitable::Hitable(int hp)
{
	maxHp = hp;
	this->hp = maxHp;
}

bool Hitable::dealDamage(float damage, float invisibleFrames)
{
	if (this->invisibleFrames > 0.0f)
		return false;
	hp -= damage;
	this->invisibleFrames = invisibleFrames;
	onHit();
	if (hp <= 0)
		deadTrigger();
	return true;
}

void Hitable::update(float deltaTime)
{
	if (invisibleFrames > 0)
		invisibleFrames -= deltaTime;
}

void Hitable::deadTrigger()
{
	Game::deleteObject(dynamic_cast<GameObject*>(this));
}