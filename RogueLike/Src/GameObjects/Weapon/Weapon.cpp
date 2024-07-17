#include "Weapon.h"
#include "../GameObject.h"
#include <fstream>

nlohmann::json Weapon::weaponData;
static Rectangle weaponSlotPos = { 0,0,0,0 };

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
	weaponSlotPos = pos;
	int i = 0;
	for (auto slot : weaponSlots)
	{
		Rectangle slotPos = Weapon::getSlotPos(pos, i++);
		DrawFrameRec(slotPos, RED, BLACK);
		if (slot)
			slot->drawIcon(RectangleDecreasSize(slotPos,4));
	}
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

void Weapon::drawWeaponNodeStats(Rectangle pos,float textSize,bool flexBox)
{
	Vector2 mouse = GetMousePosition();
	if (!CheckCollisionPointRec(mouse, weaponSlotPos))
	{
		stats.draw(pos, textSize, flexBox);
		return;
	}
	for (int i = 0; i < weaponSlots.size(); i++)
	{
		if (!CheckCollisionPointRec(mouse, getSlotPos(weaponSlotPos, i)))
			continue;
		if (!weaponSlots[i])
			break;
		weaponSlots[i]->drawNodeDescription(pos, textSize, flexBox);
		return;
	}
	stats.draw(pos, textSize, flexBox);
}

bool Weapon::addSlot(int slot, WeaponNodeItem* node)
{
	if (slot < 0 || slot >= weaponSlots.size())
		return false;
	if (weaponSlots[slot])
		return false;
	weaponSlots[slot] = node;
	updateWeaponNodesEfects();
	return true;
}

Rectangle Weapon::getSlotPos(Rectangle pos,int slot,Vector2 slotSize, float itemSpaceing)
{
	Rectangle slotPos = { pos.x,pos.y,slotSize.x,slotSize.y };
	float startSlotsX = (pos.width - (int)(pos.width / (slotPos.width + itemSpaceing)) * (slotPos.width + itemSpaceing)) / 2;
	if (startSlotsX < 0)
		startSlotsX = 0;
	startSlotsX += pos.x;
	slotPos.x = startSlotsX;
	for (int i = 0; i < slot; i++)
	{
		slotPos.x += slotPos.width + itemSpaceing;
		if (slotPos.x + slotPos.width > pos.x + pos.width)
		{
			slotPos.x = startSlotsX;
			slotPos.y += slotPos.height + itemSpaceing;
		}
	}
	return slotPos;
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
