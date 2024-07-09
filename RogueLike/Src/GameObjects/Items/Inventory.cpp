#include "Inventory.h"
#include "../GameObject.h"
#include "../Game.h"

Inventory::Inventory()
{
	ItemsStartPos.x = (GetScreenWidth() - (ItemsSpaceing.x * (InventorySize))) / 2;
	//ItemsStartPos.y = (GetScreenHeight() - (ItemsSpaceing.y * (InventorySize))) / 2;
	ItemsStartPos.y = GetScreenHeight() - ItemsSize.y - 40;
}

void Inventory::nextItem() 
{ 
	if (items[usingItem] && !items[usingItem]->canSwap())
		return;
	hideItem(); 
	usingItem = (usingItem + 1) % InventorySize; 
	showItem(); 
}

void Inventory::privItem() 
{
	if (items[usingItem] && !items[usingItem]->canSwap())
		return;
	hideItem(); 
	usingItem = (usingItem - 1 + InventorySize) % InventorySize; 
	showItem(); 
}

void Inventory::hideItem()
{
	GameObject* gm = dynamic_cast<GameObject*>(items[usingItem]);
	if (!gm)
		return;
	Game::removeObject(gm);
}

void Inventory::showItem()
{
	GameObject* gm = dynamic_cast<GameObject*>(items[usingItem]);
	if (!gm)
		return;
	Game::addObject(gm);
}

void Inventory::use(Vector2 dir, float deltaTime)
{
	if (usingItem < 0 || usingItem >= InventorySize)
		return;
	if (items[usingItem])
		items[usingItem]->use(dir, deltaTime);
}



bool Inventory::hasThisItem(Item* item)
{
	for (int i = 0; i < InventorySize; i++)
	{
		if (items[i] == item)
			return true;
	}
	return false;
}

bool Inventory::addItem(Item* item)
{
	if (hasThisItem(item))
		return true;
	for (int i = 0; i < InventorySize; i++)
	{
		if (items[i])
			continue;
		items[i] = item;
		return true;
	}
	return false;
}

void Inventory::draw()
{
	Rectangle itemPos = { ItemsStartPos.x,ItemsStartPos.y,ItemsSize.x,ItemsSize.y };
	for (int i = 0; i < InventorySize; i++)
	{
		DrawRectangleRec(itemPos, i == usingItem ? RED : BLUE);
		DrawRectangleLinesEx(itemPos, 2, BLACK);
		if (items[i])
			items[i]->drawIcone(itemPos);
		itemPos.x += ItemsSpaceing.x;
		itemPos.y += ItemsSpaceing.y;
	}
}