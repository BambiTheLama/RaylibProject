#pragma once
#include <vector>
#include "WeaponStats.h"

enum class WeaponNodeType
{
	Stat,
	Spawn,
};
enum class WeaponNodeActivation
{
	NON = 0,
	OnHit,
	OnUse,
	OnKill,
	OnEffectEnd,
};

class WeaponNode
{
	int spawnID = -1;
	WeaponNodeType type;
	WeaponNodeActivation activateTrigger;
	WeaponStats stats;
public:
	WeaponNode(WeaponStats stats);

	WeaponNode(WeaponStats stats, WeaponNodeActivation activateTrigger, int spawnID);

	WeaponStats getNextStats(WeaponNode node);

	void addToStats(WeaponStats stats);

	WeaponNodeType getType() { return type; }

	WeaponNodeActivation getActivationTrigger() { return activateTrigger; }

	int getSpawnID() { return spawnID; }

	WeaponStats getStats() { return stats; }

};

