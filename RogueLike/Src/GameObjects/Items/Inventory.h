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
	Rectangle descriptionPos = { 300,300,600,300 };
	float fontSize = 32.0f;
	Item* items[InventorySize];
	int usingItem = 0;
public:
	Inventory(GameObject* owner = nullptr);

	~Inventory();

	void update(float deltaTime);

	void nextItem();

	void privItem();

	void use(Vector2 dir, float deltaTime);

	bool hasThisItem(Item* item);

	bool addItem(Item* item);

	void draw();

	float getRange();

private:
	void hideItem();

	void showItem();
};

