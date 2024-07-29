#include "Explosion.h"
#include "../Game.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Collider/CollisionElementCircle.h"

Explosion::Explosion()
{
	pos = { 0,0,range,range };

	addCollisionElement(new CollisionElementCircle({ 0,0 }, range));
	trigger = true;
}

void Explosion::update(float deltaTime)
{
	time -= deltaTime;
	float procent = powf(sinf(time * 3.0f / timeMax), 4.0f);
	float lastRange = range;
	range = procent * (stats.range - minRange) + minRange;
	pos.width = range;
	pos.height = range;
	damage = procent * stats.damage;
	if (range < minRange)
		range = minRange;
	scaleColliderElements(range / lastRange);
	if (time <= 0)
	{
		triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
		Game::deleteObject(this);
	}

}

void Explosion::draw()
{
	Rectangle pos = getPos();
	Color c = WHITE;
	c.b = 0;
	c.g = 0;
	c.r = (unsigned char)(255 * damage / stats.damage);
	DrawCircleV({ pos.x, pos.y }, range, c);
	//DrawRectangleRec(pos, { 0,0,0,128 });
}

void Explosion::dealDamage(Collider* collider)
{

	GameObject* obj = collider->getThisObj();
	if (obj == owner)
		return;
	Hitable* hit = dynamic_cast<Hitable*>(obj);
	if (!hit)
		return;
	float damageTick = 1 / 30.0f;
	hit->dealDamage(damage * damageTick, damageTick);
	triggerNode(WeaponNodeActivation::OnHit, stats);
	if(!hit->isAlive())
		triggerNode(WeaponNodeActivation::OnKill, stats);
}

void Explosion::onTrigger(Collider* collider)
{
	dealDamage(collider);
}

void Explosion::onTriggerEnter(Collider* collider)
{
	dealDamage(collider);
}

void Explosion::updateStatsAfterSetStats()
{
	time = stats.useTime;
	timeMax = time;
	damage = stats.damage;
}