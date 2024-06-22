#include "WeaponNode.h"

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
