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

}