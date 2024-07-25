#include "WeaponNodeTrigger.h"
#include "../GameObject.h"
#include "../Game.h"
#include "../Projectal/ProjectalFactory.h"
#include <raymath.hpp>

bool WeaponNodeTrigger::activateTrigger(WeaponNodeActivation activation, GameObject* weapon,WeaponStats weaponStats, Vector2 spawnOffset)
{
	if (nodes.size() <= 0)
		return false;
	WeaponNode n = nodes[0];
	if (n.getActivationTrigger() != activation)
		return false;
	if (!weapon)
		return false;
	WeaponStats stats = n.getStats();
	for (int i = 0; i < stats.countOfUse; i++)
	{
		Projectal* projectal = ProjectalFactory::getProjectal(n.getSpawnID());
		if (!projectal)
			return false;
		projectal->setOwner(owner);
		GameObject* gm = dynamic_cast<GameObject*>(projectal);
		if (!gm)
		{
			delete projectal;
			return false;
		}

		gm->setPos(Vector2Add(weapon->getPosPoint(), spawnOffset));
		

		projectal->setWeaponNodeTrigger(getNextTriggerNode());
		projectal->setWeaponStats(n.getNextStats(weaponStats));
		float angleDiff = (((float)rand() / RAND_MAX) * 2.0f - 1.0f) * n.getStats().angle / 2;
		float angle = (weapon->getAngle() + angleDiff) * PI / 180;
		Vector2 dir;
		dir.x = cosf(angle) - sinf(angle);
		dir.y = sinf(angle) + cosf(angle);
		projectal->setDir(dir);
		Game::addObject(gm);
	}

	return true;
}

WeaponNodeTrigger WeaponNodeTrigger::getNextTriggerNode()
{
	WeaponNodeTrigger wnt;
	for (int i = 1; i < nodes.size(); i++)
		wnt.nodes.push_back(nodes[i]);
	wnt.owner = owner;
	return wnt;
}