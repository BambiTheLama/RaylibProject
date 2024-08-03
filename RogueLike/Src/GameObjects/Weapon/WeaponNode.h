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
#pragma region Constructor
	WeaponNode(){}

	WeaponNode(WeaponStats stats);

	WeaponNode(WeaponStats stats, WeaponNodeActivation activateTrigger, int spawnID);

	WeaponNode(nlohmann::json j);
#pragma endregion Constructor

#pragma region Getters
	WeaponStats getNextStats(WeaponNode node);

	WeaponNodeType getType() { return type; }

	WeaponNodeActivation getActivationTrigger() { return activateTrigger; }

	int getSpawnID() { return spawnID; }

	WeaponStats getStats() { return stats; }
#pragma endregion Getters

#pragma region Setters
	void setStats(WeaponStats ws) { this->stats = ws; }
#pragma endregion Setters

	void addToStats(WeaponStats stats);
#pragma region DrawFun
	void drawNodeDescription(Rectangle pos, float textSize, bool flexBox);
#pragma endregion DrawFun
};

