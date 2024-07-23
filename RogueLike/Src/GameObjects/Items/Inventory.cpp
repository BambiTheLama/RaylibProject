#include "Inventory.h"
#include "../GameObject.h"
#include "../Game.h"
#include "../Weapon/Weapon.h"

Inventory::Inventory(GameObject* owner)
{
	for (int i = 0; i < InventorySize; i++)
		items[i] = nullptr;
	this->owner = owner;
	ItemsStartPos.x = (GetScreenWidth() - (ItemsSpaceing.x * (InventorySize))) / 2;
	//ItemsStartPos.y = (GetScreenHeight() - (ItemsSpaceing.y * (InventorySize))) / 2;
	ItemsStartPos.y = GetScreenHeight() - ItemsSize.y - 40;
}

Inventory::~Inventory()
{
	if (itemInHand)
		delete itemInHand;
	for (int i = 0; i < InventorySize; i++)
	{
		if (items[i] && i != usingItem)
		{
			GameObject* gm = dynamic_cast<GameObject*>(items[i]);
			if (gm && Game::deleteObject(gm))
			{

			}
			else
				delete items[i];
		}
	}
	GameObject* gm = dynamic_cast<GameObject*>(items[usingItem]);
	if (gm)
	{
		Game::deleteObject(gm);
	}
	else if(items[usingItem])
	{
		delete items[usingItem];
	}

}
void Inventory::updateClick()
{
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || !showDescription)
		return;


	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (w)
		w->updateClick();


	Vector2 mouse = GetMousePosition();

	for (int i = 0; i < InventorySize; i++)
	{
		if (!CheckCollisionPointRec(mouse, getItemPos(i)))
			continue;
		hideItem();
		Item* item = items[i];
		items[i] = itemInHand;
		itemInHand = item;
		showItem();
		return;
	}
	
}

void Inventory::setItemToHand()
{
	if (items[usingItem] && !items[usingItem]->canSwap())
		return;
	if (!choseFromEq)
	{
		Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
		if (w)
			w->takeItem();
		return;
	}
	hideItem();
	Item* item = itemInHand;
	itemInHand = items[usingItem];
	items[usingItem] = item;
	showItem();
}

Rectangle Inventory::getItemPos(int i)
{
	return { ItemsStartPos.x + ItemsSpaceing.x * i,ItemsStartPos.y + ItemsSpaceing.y * i,ItemsSize.x,ItemsSize.y };
}

void Inventory::swapVisibleDescriptions()
{
	showDescription = !showDescription;
	choseFromEq = true;
	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (w)
		w->resetSlot();
	if (itemInHand && !addItem(itemInHand))
	{
		dropItem();
	}
	itemInHand = nullptr;
}

void Inventory::update(float deltaTime)
{
	if (!items[usingItem])
		return;
	items[usingItem]->update(deltaTime);


}

void Inventory::nextItem(bool moveCursor) 
{ 
	if (items[usingItem] && !items[usingItem]->canSwap())
		return;
	hideItem(); 
	usingItem = (usingItem + 1) % InventorySize; 
	showItem(); 
	if (moveCursor)
	{
		Rectangle itemPos = getItemPos(usingItem);
		SetMousePosition((int)(itemPos.x + itemPos.width / 2), (int)(itemPos.y + itemPos.height / 2));
	}

}



void Inventory::privItem(bool moveCursor)
{
	if (items[usingItem] && !items[usingItem]->canSwap())
		return;
	hideItem(); 
	usingItem = (usingItem - 1 + InventorySize) % InventorySize; 
	showItem(); 
	if (moveCursor)
	{
		Rectangle itemPos = getItemPos(usingItem);
		SetMousePosition((int)(itemPos.x + itemPos.width / 2), (int)(itemPos.y + itemPos.height / 2));
	}
}

void Inventory::nextSlot()
{
	if (choseFromEq)
	{
		nextItem();
		return;
	}
	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (!w)
	{
		choseFromEq = true;
		return;
	}
	w->nextSlot();
}

void Inventory::privSlot()
{
	if (choseFromEq)
	{
		privItem();
		return;
	}
	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (!w)
	{
		choseFromEq = true;
		return;
	}
	w->privSlot();
}

void Inventory::upSlot()
{
	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (!w)
	{
		choseFromEq = true;
		return;
	}
	if (w->upSlot())
		choseFromEq = false;
}

void Inventory::downSlot()
{
	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (!w)
	{
		choseFromEq = true;
		return;
	}
	if (w->downSlot())
	{
		choseFromEq = true;
		Rectangle itemPos = getItemPos(usingItem);
		SetMousePosition((int)(itemPos.x + itemPos.width / 2), (int)(itemPos.y + itemPos.height / 2));
	}

}

Item* Inventory::getCurrentItemToDrop()
{
	Item* i = nullptr;
	if (itemInHand)
	{
		i = itemInHand;
		itemInHand = nullptr;
	}
	else if(items[usingItem])
	{ 
		if (items[usingItem]->canSwap())
		{
			i = items[usingItem];
			items[usingItem] = nullptr;
		}
	}
	return i;
}

void Inventory::dropItem()
{
	Item* item = getCurrentItemToDrop();
	if (!item)
		return;
	item->setOwner(nullptr);
	Rectangle ownerPos = owner->getPos();

	GameObject* gm = dynamic_cast<GameObject*>(item);
	if (!gm)
		delete item;
	else 
	{
		Rectangle itemPos = gm->getPos();
		gm->setPos({ ownerPos.x + ownerPos.width / 2 - itemPos.width / 2,ownerPos.y + ownerPos.height / 2 - itemPos.height / 2 });
		if (!Game::addObject(gm))
			delete gm;
	}

}

void Inventory::hideItem()
{
	if (items[usingItem] && !items[usingItem]->canSwap())
		return;
	GameObject* gm = dynamic_cast<GameObject*>(items[usingItem]);
	if (!gm)
		return;
	Game::removeObject(gm);
}

void Inventory::showItem()
{
	if (!items[usingItem])
		return;
	if (!items[usingItem]->canSwap())
		return;
	
	items[usingItem]->setOwner(owner);
	items[usingItem]->update(0.0f);

	GameObject* gm = dynamic_cast<GameObject*>(items[usingItem]);
	if (!gm)
		return;
	Game::addObject(gm);
}

void Inventory::use(Vector2 dir, float deltaTime)
{
	if (usingItem < 0 || usingItem >= InventorySize || !items[usingItem] || showDescription)
		return;

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
		if (items[i])
		{
			items[i]->setOwner(owner);
			items[i]->setInventory(this);
			items[i]->update(0.0f);

			GameObject* gm = dynamic_cast<GameObject*>(items[i]);
			if (gm)
				Game::removeObject(gm);
			
		}

		return true;
	}
	return false;
}

void Inventory::draw()
{
	Rectangle itemPos;
	const float diffPos = 10;
	for (int i = 0; i < InventorySize; i++)
	{
		itemPos = getItemPos(i);
		if (i == usingItem)
			itemPos = RectangleIncreasSize(itemPos, diffPos);

		DrawFrameRec(itemPos, i == usingItem ? (choseFromEq ? (showDescription ? PINK : RED) : ORANGE) : BLUE);
		if (items[i])
			items[i]->drawIcon(RectangleDecreasSize(itemPos, 8), false);

		if (i == usingItem && showDescription)
		{
			itemPos = RectangleDecreasSize(itemPos, diffPos);
			if (items[i])
				items[i]->drawDescription(descriptionPos, fontSize);
		}

	}
	if (itemInHand)
	{
		Vector2 mouse = GetMousePosition();
		itemPos.x = mouse.x;
		itemPos.y = mouse.y;
		DrawFrameRec(itemPos, ORANGE);
		itemInHand->drawIcon(RectangleDecreasSize(itemPos, 8));
	}


}

float Inventory::getRange()
{
	if (usingItem < 0 || usingItem >= InventorySize || !items[usingItem])
		return 0.0f;
	Weapon* w = dynamic_cast<Weapon*>(items[usingItem]);
	if (!w)
		return 0.0f;
	return w->getRange();
}