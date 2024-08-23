#pragma once
#include "../WaveCollapsFun.h"
#include "raylib.hpp"
#include <string>

enum class EnemiesID
{
	Slime=0,
	Goblin,
	Skeletron
};

class GameObject;

GameObject* getRoomElement(int ID, float x, float y, float w, float h);

void setUpRoomElement(std::string path);

void setUpFloor(int floor);

GameObject* getEnemy(EnemiesID ID);

GameObject* getEnemy(int ID, Rectangle pos);

GameObject* getChest(int ID, Rectangle pos);

GameObject* getObject(int ID, Rectangle pos);
