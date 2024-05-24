#include "RoomElements.h"
#include "../../GameObjects/Characters/Wall.h"

GameObject* getRoomElement(int ID,int x,int y)
{
	if (ID <= 0)
		return NULL;
	return new Wall(x, y);
}

BlockType getRoomElementType(int ID)
{
	if (ID <= 0)
		return BlockType::NON;

	return BlockType::Wall;
}