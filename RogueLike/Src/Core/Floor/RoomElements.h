#pragma once
#include "../WaveCollapsFun.h"
#include "raylib.hpp"

class GameObject;

GameObject* getRoomElement(int ID, int x, int y, int w, int h);

GameObject* getObject(int ID, Rectangle pos);

BlockType getRoomElementType(int ID);
