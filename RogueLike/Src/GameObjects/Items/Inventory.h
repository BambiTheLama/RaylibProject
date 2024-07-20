#pragma once
#include "raylib.hpp"
#include "Item.h"
#include <vector>

#define InventorySize 10

class Inventory
{
	GameObject* owner;
	Vector2 ItemsStartPos = { 32,32 };
	Vector2 ItemsSize = { 64,64 };
	Vector2 ItemsSpaceing = { 75,0 };
	Rectangle descriptionPos = { 100,100,600,300 };
	float fontSize = 32.0f;
	Item* items[InventorySize];
	Item* itemInHand = nullptr;
	int usingItem = 0;
	bool showDescription = false;
	bool choseFromEq = true;
public:
	Inventory(GameObject* owner = nullptr);

	~Inventory();

	void updateClick();

	void update(float deltaTime);

	void nextItem();

	void privItem();

	void nextSlot();

	void privSlot();

	void upSlot();

	void downSlot();

	void use(Vector2 dir, float deltaTime);

	bool hasThisItem(Item* item);

	bool addItem(Item* item);

	void draw();

	float getRange();

	void setItemToHand();

	Item* getHandItem() { return itemInHand; }

	void setHandItem(Item* i) { itemInHand = i; }

	Rectangle getItemPos(int i);

	void swapVisibleDescriptions();

	bool isDescriptionShowed() { return showDescription; }
private:
	void hideItem();

	void showItem();
};

