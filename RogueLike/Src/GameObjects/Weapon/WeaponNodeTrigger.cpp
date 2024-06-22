#include "WeaponNodeTrigger.h"
#include "../GameObject.h"
#include "../Game.h"
#include "../Projectal/ProjectalFactory.h"
#include <raymath.hpp>

bool WeaponNodeTrigger::activateTrigger(WeaponNodeActivation activation, GameObject* weapon)
{
	if (nodes.size() <= 0)
		return false;
	WeaponNode n = nodes[0];
	if (n.getActivationTrigger() != activation)
		return false;
	if (!weapon)
		return false;
	Projectal* projectal = ProjectalFactory::getProjectal(n.getSpawnID());
	if (!projectal)
		return false;
	GameObject* gm = dynamic_cast<GameObject*>(projectal);
	if (!gm)
	{
		delete projectal;
		return false;
	}
	gm->setPos(weapon->getPosPoint());
	projectal->setWeaponNodeTrigger(getNextTriggerNode());
	projectal->setWeaponStats(n.getStats());
	float angleDiff = (((float)rand() / RAND_MAX) * 2.0f - 1.0f) * n.getStats().angle;
	float angle = weapon->getAngle() * PI / 180;;
	Vector2 dir;
	dir.x = cos(angle) - sin(angle);
	dir.y = sin(angle) + cos(angle);
	projectal->setDir(dir);
	return Game::addObject(gm);
}

WeaponNodeTrigger WeaponNodeTrigger::getNextTriggerNode()
{
	WeaponNodeTrigger wnt;
	for (int i = 1; i < nodes.size(); i++)
		wnt.nodes.push_back(nodes[i]);
	
	return wnt;
}