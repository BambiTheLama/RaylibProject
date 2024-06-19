#pragma once
#include <vector>
#include "WeaponStats.h"

enum class WeaponNodeType
{
	Stat,Spawn
};
enum class WeaponNodeActivation
{
	OnHit,OnUse,OnKill
};

class WeaponNode
{
	std::vector<WeaponNode> nextNode;
	WeaponNodeType type;
	WeaponNodeActivation activateTrigger;
	WeaponStats stats;
public:
	WeaponNode(WeaponNodeActivation activateTrigger, WeaponStats stats, WeaponNodeType type);

	WeaponStats getNextStats(WeaponNode node);

	void addToEndNode(WeaponNode node);

	std::vector<WeaponNode> getNextWeaponNode();

	WeaponNodeType getType() { return type; }

	WeaponNodeActivation getActivationTrigger() { return activateTrigger; }

};

