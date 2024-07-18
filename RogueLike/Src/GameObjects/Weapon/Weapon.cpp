#include "Weapon.h"
#include "../GameObject.h"
#include <fstream>
#include "../Items/Inventory.h"

nlohmann::json Weapon::weaponData;
static Rectangle weaponSlotPos = { 0,0,0,0 };

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
	for (auto wni : weaponSlots)
	{
		if(wni)
			delete wni;
	}
	weaponSlots.clear();
}

void Weapon::update() 
{ 
	if (!Item::showDescriptions || !inventory || !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return;
	Vector2 mouse = GetMousePosition();
	int i = 0;
	for (auto slot : weaponSlots)
	{
		Rectangle slotPos = Weapon::getSlotPos(weaponSlotPos, i++);
		if (!CheckCollisionPointRec(mouse, slotPos))
			continue;
		
		Item* itemInHand = inventory->getHandItem();
		WeaponNodeItem* wni = dynamic_cast<WeaponNodeItem*>(itemInHand);
		if (!itemInHand || wni)
		{
			inventory->setHandItem(slot);
			weaponSlots[i - 1] = wni;
		}
		break;

	}
	updateWeaponNodesEfects();
}

WeaponNodeItem* Weapon::removeWeaponNodeItem(int n)
{
	if (n<0 || n>weaponSlots.size())
		return nullptr;
	WeaponNodeItem* wni = weaponSlots[n];
	weaponSlots[n] = nullptr;
	return wni;
}

void Weapon::drawWeaponDescription(Rectangle pos,float textSize)
{
	weaponSlotPos = pos;
	int i = 0;
	Vector2 mouse = GetMousePosition();
	for (auto slot : weaponSlots)
	{
		Rectangle slotPos = Weapon::getSlotPos(pos, i++);
		bool isCursorAt = CheckCollisionPointRec(mouse, slotPos);
		DrawFrameRec(slotPos, isCursorAt ? ORANGE : RED, BLACK);
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
		weaponSlots[i]->drawDescription(pos, textSize);
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

Rectangle Weapon::getSlotPos(Rectangle pos, int slot, int row, Vector2 slotSize, float itemSpaceing)
{
	Rectangle slotPos = { pos.x,pos.y,slotSize.x,slotSize.y };
	int slotsInColumns = (int)(pos.width / (slotPos.width + itemSpaceing));
	float startSlotsX = (pos.width - slotsInColumns * (slotPos.width + itemSpaceing)) / 2;
	if (startSlotsX < 0)
		startSlotsX = 0;
	startSlotsX += pos.x;
	slotPos.x = startSlotsX + (slot % slotsInColumns) * (slotPos.width + itemSpaceing) + itemSpaceing / 2;
	slotPos.y += (row + (int)(slot / slotsInColumns)) * (slotPos.height + itemSpaceing) + itemSpaceing;
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
	for (WeaponNode& wn : activationNodes)
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
