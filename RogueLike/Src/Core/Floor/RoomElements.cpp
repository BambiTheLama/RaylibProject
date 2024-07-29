#include "RoomElements.h"
#include "../../GameObjects/Characters/Wall.h"
#include "../../GameObjects/Characters/BossWall.h"
#include "../../GameObjects/Characters/SpawnPoint.h"
#include "../../GameObjects/Characters/BossEnterWall.h"
#include "../../GameObjects/Characters/Wolf.h"
#include "../../GameObjects/Characters/LootBlock.h"
#include "../../GameObjects/Characters/Chest.h"
GameObject* getRoomElement(int ID, float x, float y, float w, float h)
{
	if (ID <= 0)
		return NULL;
	switch (ID)
	{
	case 1:
		return new Wall(x, y, w, h);
	case 2:
		return new BossWall(x, y, w, h);
	case 3:
		return new SpawnPoint(x, y, BlockType::PlayerSpawnPoint);
	case 7:
		return new SpawnPoint(x, y, BlockType::BossSpawnPoint);
	case 8:
		return new BossEnterWall(x, y, w, h);
	case 9:
		return new SpawnPoint(x, y, BlockType::ElitEnemySpawn);
	default:
		break;
	}
	return NULL;
}



GameObject* getEnemy(int ID, Rectangle pos)
{
	if (ID < 0)
		return NULL;
	switch (ID)
	{
	case 0:
		return new Wolf(pos.x + pos.width / 2, pos.y + pos.height / 2);
	default:
		break;
	}
	return NULL;
}

GameObject* getChest(int ID, Rectangle pos)
{
	if (ID < 0)
		return NULL;
	
	return new Chest(pos, ID);
}

GameObject* getObject(int ID, Rectangle pos)
{
	if (ID < 0)
		return NULL;
	switch (ID)
	{
	case 0:
		return new LootBlock(pos.x, pos.y);
	default:
		break;
	}
	return NULL;
}