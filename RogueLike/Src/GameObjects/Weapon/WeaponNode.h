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

std::string to_string(WeaponNodeActivation wna);


class WeaponNode
{
	int spawnID = -1;
	WeaponNodeType type = WeaponNodeType::Stat;
	WeaponNodeActivation activateTrigger = WeaponNodeActivation::NON;
	WeaponStats stats;
public:
	WeaponNode(){}

	WeaponNode(WeaponStats stats);

	WeaponNode(WeaponStats stats, WeaponNodeActivation activateTrigger, int spawnID);

	WeaponStats getNextStats(WeaponNode node);

	void addToStats(WeaponStats stats);

	WeaponNodeType getType() { return type; }

	WeaponNodeActivation getActivationTrigger() { return activateTrigger; }

	int getSpawnID() { return spawnID; }

	WeaponStats getStats() { return stats; }

	void drawNodeDescription(Rectangle pos, float textSize, bool flexBox);
};

