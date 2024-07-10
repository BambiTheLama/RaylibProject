#include "Weapon.h"
#include "../GameObject.h"
#include <fstream>

nlohmann::json Weapon::weaponData;

Weapon::Weapon()
{

}

void Weapon::update() 
{ 
	if (thisObj)
		thisObj->update(0.0f);
	else
		findThisObject();
}

bool Weapon::triggerNode(WeaponNodeActivation activation, WeaponStats stats)
{
	if (!thisObj)
		findThisObject();
	if (!thisObj)
		return false;
	printf("U�yto %d\n", (int)activation);
	return weaponNodeTrigger.activateTrigger(activation, thisObj, stats);
	return false;
}

WeaponNode* Weapon::removeSlot(int slot)
{
	if (slot < 0 || slot >= weaponSlots.size())
		return nullptr;
	if(!weaponSlots[slot])
		return nullptr;
	WeaponNode* node = weaponSlots[slot];
	weaponSlots[slot] = nullptr;
	updateWeaponNodesEfects();
	return node;
}

bool Weapon::addSlot(int slot, WeaponNode* node)
{
	if (slot < 0 || slot >= weaponSlots.size())
		return false;
	if (weaponSlots[slot])
		return false;
	weaponSlots[slot] = node;
	updateWeaponNodesEfects();
}

void Weapon::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
}

void Weapon::loadWeaponData(std::string weaponDataPath)
{
	std::ifstream reader;
	reader.open(weaponDataPath);
	if (reader.is_open())
	{
		reader >> weaponData;
		reader.close();
	}
}

void Weapon::updateWeaponNodesEfects()
{
	std::vector<WeaponNode> activationNodes;
	for (auto wn: weaponSlots)
	{
		if (!wn)
			continue;
		if (WeaponNodeType::Stat == wn->getType())
		{
			if (activationNodes.size() <= 0)
			{
				stats += wn->getStats();
			}
			else
			{
				activationNodes[activationNodes.size() - 1].addToStats(wn->getStats());
			}
		}
		else
		{
			activationNodes.push_back(WeaponNode(*wn));
		}
	}
	WeaponNodeTrigger wnt;
	for (auto wn : activationNodes)
		wnt.pushBackNodeTrigger(wn);
	weaponNodeTrigger = wnt;
}

void Weapon::setNumberOfSlots(int slots)
{
	if (slots < 0)
		return;
	if (weaponSlots.size() > slots)
	{
		while (weaponSlots.size() > slots)
			weaponSlots.pop_back();
	}
	else
	{
		while (weaponSlots.size() < slots)
			weaponSlots.push_back(nullptr);
	}
	updateWeaponNodesEfects();
}
