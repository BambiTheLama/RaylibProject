#pragma once
#include "../WaveCollapsFun.h"

class GameObject;

GameObject* getRoomElement(int ID, int x, int y, int w, int h);

BlockType getRoomElementType(int ID);
