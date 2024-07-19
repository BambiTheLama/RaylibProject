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

WeaponNode::WeaponNode(WeaponStats stats)
{
	this->activateTrigger = WeaponNodeActivation::NON;
	this->stats = stats;
	this->type = WeaponNodeType::Stat;
	this->spawnID = -1;
}

WeaponNode::WeaponNode(WeaponStats stats, WeaponNodeActivation activateTrigger, int spawnID)
{
	this->activateTrigger = activateTrigger;
	this->stats = stats;
	this->type = WeaponNodeType::Spawn;
	this->spawnID = spawnID;
}

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

void WeaponNode::addToStats(WeaponStats stats)
{
	this->stats += stats;
}

void WeaponNode::drawNodeDescription(Rectangle pos, float textSize, bool flexBox)
{
	switch (type)
	{
	case WeaponNodeType::Stat:
	{
		std::string str = "     {Stats}\n";
		stats.draw(pos, textSize, flexBox, true, str, true, true);
	}
		break;
	case WeaponNodeType::Spawn:
	{
		std::string str = "     {Spawn}: " + std::to_string(spawnID) + "\n";
		str += "     {Activaction}: {" + to_string(activateTrigger) + "}\n";
		stats.draw(pos, textSize, flexBox, true, str);
	}
		break;
	default:
		break;
	}
}

