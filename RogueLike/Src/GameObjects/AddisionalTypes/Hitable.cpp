#include "Hitable.h"
#include "../Game.h"
#include "../ParticleText.h"
#include <string>

int Hitable::showParticle = 0;//0b11111;

Hitable::Hitable(float hp)
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
	GameObject* gm = dynamic_cast<GameObject*>(this);
	if (gm && ((int)gm->getType() & showParticle) != 0)
	{
		Vector2 pos = gm->getPosPoint();
		std::string text = std::to_string(damage);
		for(int i=0;i<4;i++)
			text.pop_back();
		Game::addObject(new ParticleText(pos.x, pos.y, text));
	}

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

void Hitable::draw(Rectangle pos) {
	DrawRectangleRec(pos, GRAY);
	DrawRectangleRec({ pos.x, pos.y, pos.width * getProcentHp(), pos.height }, GREEN);
	DrawRectangleLinesEx(pos, 3, BLACK);
}