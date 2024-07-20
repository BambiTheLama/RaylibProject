#include "StandardProjectal.h"
#include "../Collider/CollisionElementCircle.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"

StandardProjectal::StandardProjectal()
{
	//drawOrder = 10;
	pos = { 0,0,32,32 };
	collisionElemnets.push_back(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 2));
	trigger = true;
	
}

void StandardProjectal::start()
{
	triggerNode(WeaponNodeActivation::OnUse, stats);
}

void StandardProjectal::destroy()
{
	triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
}

void StandardProjectal::update(float deltaTime)
{
	pos.x += dir.x * stats.speed * deltaTime;
	pos.y += dir.y * stats.speed * deltaTime;
	range -= stats.speed * deltaTime;
	if (range <= 0)
	{

		Game::deleteObject(this);
	}

}

void StandardProjectal::draw()
{
	DrawCircleV({ pos.x + pos.width / 2, pos.y + pos.height / 2 }, pos.height / 2, BLACK);
}



void StandardProjectal::onTriggerEnter(Collider* collider)
{
	GameObject* colObj = collider->getThisObj();
	if (!colObj)
		return;
	if ((int)colObj->getType() & (int)ObjectType::Enemy)
	{
		Hitable* hit = dynamic_cast<Hitable*>(colObj);
		if (hit)
		{
			hit->dealDamage(stats.damage);
			if (!hit->isAlive())
				triggerNode(WeaponNodeActivation::OnKill, stats);
			pirce--;
			if (pirce <= 0)
			{
				Game::deleteObject(this);
			}

			triggerNode(WeaponNodeActivation::OnHit, stats);
		}

	}
	else if ((int)colObj->getType() & (int)ObjectType::Wall)
	{
		Vector2 collisonDir = getCollisionDir(collider);
		if (abs(collisonDir.x) > abs(collisonDir.y))
			dir.x = -dir.x;
		else
			dir.y = -dir.y;
		if (bounce-- <= 0)
		{
			triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
			Game::deleteObject(this);
		}
	}
}

float StandardProjectal::getAngle()
{
	return Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / PI;
}

void StandardProjectal::updateStatsAfterSetStats()
{
	pirce = stats.pirce;
	bounce = stats.bounce;
	range = stats.range;
	
}