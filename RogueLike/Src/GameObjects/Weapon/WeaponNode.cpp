#include "WeaponNode.h"

WeaponNode::WeaponNode(WeaponNodeActivation activateTrigger, WeaponStats stats, WeaponNodeType type)
{
	this->activateTrigger = activateTrigger;
	this->stats = stats;
	this->type = type;
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

void WeaponNode::addToEndNode(WeaponNode node)
{
	nextNode.push_back(node);
}

std::vector<WeaponNode> WeaponNode::getNextWeaponNode()
{
	return nextNode;
}