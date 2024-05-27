#include "RoomElements.h"
#include "../../GameObjects/Characters/Wall.h"
#include "../../GameObjects/Characters/BossWall.h"

GameObject* getRoomElement(int ID,int x,int y)
{
	if (ID <= 0)
		return NULL;
	switch (ID)
	{
	case 1:
		return new Wall(x, y);
	case 2:
		return new BossWall(x, y);
	default:
		break;
	}
	return NULL;
}

BlockType getRoomElementType(int ID)
{
	if (ID <= 0)
		return BlockType::NON;

	return BlockType::Wall;
}