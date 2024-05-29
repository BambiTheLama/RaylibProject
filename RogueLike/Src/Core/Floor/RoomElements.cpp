#include "RoomElements.h"
#include "../../GameObjects/Characters/Wall.h"
#include "../../GameObjects/Characters/BossWall.h"

GameObject* getRoomElement(int ID, int x, int y, int w, int h)
{
	if (ID <= 0)
		return NULL;
	switch (ID)
	{
	case 1:
		return new Wall(x, y,w,h);
	case 2:
		return new BossWall(x, y, w, h);
	default:
		break;
	}
	return NULL;
}

BlockType getRoomElementType(int ID)
{
	if (ID <= 0)
		return BlockType::NON;
	if (ID <= 2)
		return BlockType::Wall;
	if (ID <= 3)
		return BlockType::PlayerSpawnPoint;
	if (ID <= 4)
		return BlockType::ChestSpawnPoint;
	if (ID <= 5)
		return BlockType::LootSpawnPoint;
	if (ID <= 6)
		return BlockType::EnemySpawnPoint;
	if (ID <= 7)
		return BlockType::BossSpawnPoint;
	if (ID <= 8)
		return BlockType::BossEnterWall;
	return BlockType::NON;
}