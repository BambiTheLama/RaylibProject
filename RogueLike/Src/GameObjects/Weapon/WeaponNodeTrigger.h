#pragma once
#include <vector>
#include "WeaponNode.h"
#include "raylib.h"

class GameObject;
class WeaponNodeTrigger
{
	std::vector<WeaponNode> nodes;
	GameObject* owner = nullptr;
public:
	void setNodesTrigger(std::vector<WeaponNode> nodes) { this->nodes = nodes; }

	WeaponNode getNode(int i) { return nodes[i]; }

	void setOwner(GameObject* o) { this->owner = o; }

	void pushBackNodeTrigger(WeaponNode node) { nodes.push_back(node); }

	bool activateTrigger(WeaponNodeActivation activation, GameObject* weapon, WeaponStats stats, Vector2 spawnOffset=Vector2());

	WeaponNodeTrigger getNextTriggerNode();
};

