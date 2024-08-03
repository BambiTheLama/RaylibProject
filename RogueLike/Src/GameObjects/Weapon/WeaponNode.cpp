#include "WeaponNode.h"

std::string to_string(WeaponNodeActivation wna)
{
	switch (wna)
	{
	case WeaponNodeActivation::NON:
		return "NON";
	case WeaponNodeActivation::OnHit:
		return "OnHit";
	case WeaponNodeActivation::OnUse:
		return "OnUse";
	case WeaponNodeActivation::OnKill:
		return "OnKill";
	case WeaponNodeActivation::OnEffectEnd:
		return "OnEffectEnd";
	default:
		break;
	}
	return "";
}

int getWeaponTier(nlohmann::json j)
{
	if (!j.contains("Tiers"))
		return 0;
	int tiers = (int)j["Tiers"].size();
	if (tiers <= 1)
		return 0;
	int sum = 0;
	for (int i = 0; i < tiers; i++)
		sum += j["Tiers"][i];
	if (sum <= 0)
		return 0;
	
	int randSum = rand() % sum;
	sum = 0;
	for (int i = 0; i < tiers; i++)
	{
		sum += j["Tiers"][i];
		if (sum >= randSum)
			return i;

	}
	return tiers - 1;
}

#pragma region Constructor
WeaponNode::WeaponNode(WeaponStats stats)
{
	this->activateTrigger = WeaponNodeActivation::NON;
	this->stats = stats;
	this->type = WeaponNodeType::Stat;
	this->spawnID = -1;
}

WeaponNode::WeaponNode(nlohmann::json j)
{
	int tier = getWeaponTier(j);
	if (j.contains("Type"))
		type = (WeaponNodeType)j["Type"];
	if (j.contains("Activation"))
		activateTrigger = j["Activation"];
	if (j.contains("Spawn"))
		spawnID = j["Spawn"];
	if (j.contains("Stats"))
		stats.readStatsFromWeapon(j, tier);
}

WeaponNode::WeaponNode(WeaponStats stats, WeaponNodeActivation activateTrigger, int spawnID)
{
	this->activateTrigger = activateTrigger;
	this->stats = stats;
	this->type = WeaponNodeType::Spawn;
	this->spawnID = spawnID;
}
#pragma endregion Constructor

#pragma region Getters
WeaponStats WeaponNode::getNextStats(WeaponNode node)
{
	WeaponStats stats = this->stats;
	WeaponStats lastStats = node.stats;
	stats.damage += stats.damageMultiplier * lastStats.damage;
	stats.knockbackMultiplier += stats.knockbackMultiplier * lastStats.knockback;
	stats.range += stats.rangeMultiplier * lastStats.range;
	stats.speed += stats.speedMultiplier * lastStats.speed;
	stats.useTime += stats.useTimeMultiplier * lastStats.useTime;
	stats.reloadTime += stats.reloadTimeMultiplier * lastStats.reloadTime;
	return stats;
}
#pragma endregion Getters

void WeaponNode::addToStats(WeaponStats stats)
{
	this->stats += stats;
}

#pragma region DrawFun
void WeaponNode::drawNodeDescription(Rectangle pos, float textSize, bool flexBox)
{
	switch (type)
	{
	case WeaponNodeType::Stat:
	{
		std::string str = "     {Stats}\n";
		stats.draw(pos, textSize, flexBox, true, str, true, true, true);
	}
		break;
	case WeaponNodeType::Spawn:
	{
		std::string str = "     {Spawn}: " + std::to_string(spawnID) + "\n";
		str += "     {Activaction}: {" + to_string(activateTrigger) + "}\n";
		stats.draw(pos, textSize, flexBox, true, str, false, false, true);
	}
		break;
	default:
		break;
	}
}
#pragma endregion DrawFun


