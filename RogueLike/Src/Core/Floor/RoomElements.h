#pragma once
#include "../WaveCollapsFun.h"
#include "raylib.hpp"

class GameObject;



GameObject* getRoomElement(int ID, float x, float y, float w, float h);

GameObject* getEnemy(int ID, Rectangle pos);

GameObject* getObject(int ID, Rectangle pos);

BlockType getRoomElementType(int ID);

int getRoomElementType(BlockType type);
