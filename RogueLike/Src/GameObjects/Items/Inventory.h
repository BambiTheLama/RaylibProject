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
	const Vector2 descriptionStart = { -1900,100 };
	const Vector2 descriptionEnd = { 2000,100 };
	float timerDesctiption = 0.0f;
	float timerDesctiptionMax = 1.0f;

	float fontSize = 32.0f;
	Item* items[InventorySize];
	Item* itemInHand = nullptr;
	int usingItem = 0;
	bool showDescription = false;
	bool choseFromEq = true;
public:
	Inventory(GameObject* owner = nullptr);

	~Inventory();

#pragma region Slots
	void updateClick();

	void nextItem(bool moveCursor = true);

	void privItem(bool moveCursor = true);

	void nextSlot();

	void privSlot();

	void upSlot();

	void downSlot();

	bool addItem(Item* item);

	void dropItem();
#pragma endregion Slots

	void update(float deltaTime, Vector2 dir);

	void use(Vector2 dir, float deltaTime);

	void stopUse(Vector2 dir, float deltaTime);
	
	void draw();

	void drawItem();
#pragma region Getters
	Item* getCurrentItemToDrop();

	float getRange();

	Item* getHandItem() { return itemInHand; }

	Rectangle getItemPos(int i);

	bool isDescriptionShowed() { return showDescription; }
	
	bool hasThisItem(Item* item);
#pragma endregion Getters

#pragma region Setters
	void setItemToHand();

	void setHandItem(Item* i) { itemInHand = i; }

	void swapVisibleDescriptions();

	void setTarget(int target);
#pragma endregion Setters




private:
	bool isItemInMap();

	void hideItem();

	void showItem();
};

