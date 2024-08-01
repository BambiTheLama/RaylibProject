#pragma once
#include <vector>
#include "WeaponStats.h"

enum class WeaponNodeType :char
{
	Stat,
	Spawn,
};
enum class WeaponNodeActivation
{
	NON = 0,
	OnUse,
	OnHit,
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

	WeaponNode(nlohmann::json j);

	WeaponStats getNextStats(WeaponNode node);

	void addToStats(WeaponStats stats);

	WeaponNodeType getType() { return type; }

	WeaponNodeActivation getActivationTrigger() { return activateTrigger; }

	int getSpawnID() { return spawnID; }

	WeaponStats getStats() { return stats; }

	void setStats(WeaponStats ws) { this->stats = ws; }

	void drawNodeDescription(Rectangle pos, float textSize, bool flexBox);
};

