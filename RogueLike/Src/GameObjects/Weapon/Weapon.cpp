#include "Weapon.h"
#include "../GameObject.h"
#include <fstream>

nlohmann::json Weapon::weaponData;

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
	printf("KURWA usuwam broñ\n");
	for (auto wni : weaponSlots)
	{
		if(wni)
			delete wni;
	}
	weaponSlots.clear();
}

void Weapon::update() 
{ 
	if (thisObj)
		thisObj->update(0.0f);
	else
		findThisObject();
}

void Weapon::drawWeaponDescription(Rectangle pos,float textSize)
{
	stats.draw({ pos.x+pos.width,pos.y,0,0 }, textSize,true,false);
}

bool Weapon::triggerNode(WeaponNodeActivation activation, WeaponStats stats)
{
	if (!thisObj)
		findThisObject();
	if (!thisObj)
		return false;
	printf("U¿yto %d\n", (int)activation);
	return weaponNodeTrigger.activateTrigger(activation, thisObj, stats);
	return false;
}

WeaponNodeItem* Weapon::removeSlot(int slot)
{
	if (slot < 0 || slot >= weaponSlots.size())
		return nullptr;
	if(!weaponSlots[slot])
		return nullptr;
	WeaponNodeItem* node = weaponSlots[slot];
	weaponSlots[slot] = nullptr;
	updateWeaponNodesEfects();
	return node;
}

bool Weapon::addSlot(int slot, WeaponNodeItem* node)
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
	for (auto wni: weaponSlots)
	{
		if (!wni)
			continue;
		WeaponNode* wn = wni->getWeaponNode();
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
