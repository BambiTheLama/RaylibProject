#pragma once
#include <vector>
#include "WeaponNode.h"
class GameObject;
class WeaponNodeTrigger
{
	std::vector<WeaponNode> nodes;
public:
	void setNodesTrigger(std::vector<WeaponNode> nodes) { this->nodes = nodes; }

	void pushBackNodeTrigger(WeaponNode node) { nodes.push_back(node); }

	bool activateTrigger(WeaponNodeActivation activation, GameObject* weapon, WeaponStats stats);

	WeaponNodeTrigger getNextTriggerNode();
};

