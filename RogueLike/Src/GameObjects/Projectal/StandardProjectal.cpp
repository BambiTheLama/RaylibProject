#include "StandardProjectal.h"
#include "../Collider/CollisionElementCircle.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"

StandardProjectal::StandardProjectal()
{
	drawOrder = 10;
	pos = { 0,0,32,32 };
	collisionElemnets.push_back(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 4));
	trigger = true;
}

void StandardProjectal::update(float deltaTime)
{
	pos.x += dir.x * stats.speed * deltaTime;
	pos.y += dir.y * stats.speed * deltaTime;
	time -= deltaTime;
	if (time <= 0)
	{
		triggerNode(WeaponNodeActivation::OnEffectEnd);
		Game::deleteObject(this);
	}

}

void StandardProjectal::draw()
{
	DrawRectangleRec(pos, RED);
}

void StandardProjectal::onTriggerEnter(Collider* collider)
{
	GameObject* colObj = collider->getThisObj();
	if (!colObj)
		return;
	if (colObj->getType() == ObjectType::Enemy)
	{
		Hitable* hit = dynamic_cast<Hitable*>(colObj);
		if (hit)
		{
			hit->dealDamage(stats.damage);
			if (!hit->isAlive())
				triggerNode(WeaponNodeActivation::OnKill);
			pirce--;
			if (pirce <= 0)
				Game::deleteObject(this);
			triggerNode(WeaponNodeActivation::OnHit);
		}

	}
	else if (colObj->getType() == ObjectType::Wall)
	{
		dir.x = -dir.x;
		dir.y = -dir.y;
	}
}

float StandardProjectal::getAngle()
{
	return Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / PI;
}