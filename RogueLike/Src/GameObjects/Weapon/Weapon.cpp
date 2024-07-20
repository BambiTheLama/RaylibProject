#include "Weapon.h"
#include "../GameObject.h"
#include <fstream>
#include "../Items/Inventory.h"
#include "math.h"

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

void Weapon::updateClick()
{ 
	if (!inventory)
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
			inventory->setHandItem(removeSlot(i - 1));
			addSlot(i - 1, wni);
		}
		break;

	}
	updateWeaponNodesEfects();
}



void Weapon::nextSlot()
{
	if (cursorAt +1 < weaponSlots.size())
		cursorAt++;
}

void Weapon::privSlot()
{
	if (cursorAt > 0)
		cursorAt--;
}

bool Weapon::upSlot()
{
	if (cursorAt < 0)
	{
		cursorAt = 0;
		return true;
	}
	return true;
}

bool Weapon::downSlot()
{
	cursorAt = -1;
	return true;
}

void Weapon::takeItem()
{
	if (cursorAt < 0 || cursorAt >= weaponSlots.size())
		return;
	Item* item = inventory->getHandItem();
	if (!item)
	{
		inventory->setHandItem(removeSlot(cursorAt));
		return;
	}
	WeaponNodeItem* wni = dynamic_cast<WeaponNodeItem*>(item);
	if (!wni)
		return;
	inventory->setHandItem(removeSlot(cursorAt));
	addSlot(cursorAt, wni);
	
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
		if (CheckCollisionPointRec(mouse, slotPos))
		{
			cursorAt = i - 1;
		}

		bool isCursorAt = i - 1 == cursorAt;
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
	printf("U�yto %d\n", (int)activation);
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
	if (node)
		node->getWeaponNode()->setStats(weaponSlotsDifoltStat[slot]);
	weaponSlots[slot] = nullptr;
	weaponSlotsDifoltStat[slot] = WeaponStats();
	updateWeaponNodesEfects();
	return node;
}

void Weapon::drawWeaponNodeStats(Rectangle pos,float textSize,bool flexBox)
{
	if (cursorAt >= 0 && cursorAt < weaponSlots.size() && weaponSlots[cursorAt])
	{
		weaponSlots[cursorAt]->drawDescription(pos, textSize);
	}
	else
	{
		stats.draw(pos, textSize, flexBox);
	}

}



bool Weapon::addSlot(int slot, WeaponNodeItem* node)
{
	if (slot < 0 || slot >= weaponSlots.size())
		return false;
	if (weaponSlots[slot])
		return false;
	if (!node)
		return false;
	weaponSlots[slot] = node;
	weaponSlotsDifoltStat[slot] = node->getWeaponNode()->getStats();
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
	for (int i = 0; i < weaponSlots.size(); i++)
	{
		if (!weaponSlots[i])
			continue;
		weaponSlots[i]->getWeaponNode()->setStats(weaponSlotsDifoltStat[i]);
	}
	stats = difoltStats;
	std::vector<WeaponNode*> activationNodes;
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
				activationNodes[activationNodes.size() - 1]->addToStats(wn->getStats());
			}
		}
		else
		{
			activationNodes.push_back(wn);
		}
	}
	WeaponNodeTrigger wnt;
	for (WeaponNode* wn : activationNodes)
		wnt.pushBackNodeTrigger(*wn);
	weaponNodeTrigger = wnt;
	printf(stats.toString().c_str());
}

void Weapon::setNumberOfSlots(int slots)
{
	if (slots < 0)
		return;
	if (weaponSlots.size() > slots)
	{
		while (weaponSlots.size() > slots)
		{
			weaponSlots.pop_back();
			weaponSlotsDifoltStat.pop_back();
		}

	}
	else
	{
		while (weaponSlots.size() < slots)
		{
			weaponSlots.push_back(nullptr);
			weaponSlotsDifoltStat.push_back(WeaponStats());
		}

	}
	updateWeaponNodesEfects();
}
void Weapon::readFromWeaponData(std::string weaponType, int weaponTier, int variant)
{
	if (!weaponData.contains(weaponType))
		return;
	if (weaponData[weaponType].contains("Slots"))
	{
		int tiers = weaponData[weaponType]["Slots"].size();
		if (weaponTier >= tiers)
			weaponTier = tiers - 1;
		if (weaponTier >= 0 && tiers > 0)
		{
			int slots = 0;
			if (weaponData[weaponType]["Slots"][weaponTier].size() > 1)
			{
				int slotsMin = weaponData[weaponType]["Slots"][weaponTier][0];
				int slotsMax = weaponData[weaponType]["Slots"][weaponTier][1];
				slots = std::min(slotsMin, slotsMax);
				if (slotsMin != slotsMax)
					slots += rand() % (abs(slotsMax - slotsMin) + 1);
			}
			else if (weaponData[weaponType]["Slots"][weaponTier].size() > 0)
			{
				slots = weaponData[weaponType]["Slots"][weaponTier];
			}
			setNumberOfSlots(slots);
		}
	}
	if (weaponData[weaponType].contains("Textures"))
	{
		int numberOfTextures = (int)weaponData[weaponType]["Textures"].size();
		if (numberOfTextures > 0)
		{
			int textureId = variant % numberOfTextures;
			std::string texturePath = weaponData[weaponType]["Textures"][textureId];
			texture = TextureController(texturePath);
		}
	}
	if (weaponData[weaponType].contains("RotationPoint"))
	{
		rotationPoint.x = weaponData[weaponType]["RotationPoint"][0];
		rotationPoint.y = weaponData[weaponType]["RotationPoint"][1];
	}
	stats.readStatsFromWeapon(weaponData[weaponType], weaponTier);
	setStats(stats);
}