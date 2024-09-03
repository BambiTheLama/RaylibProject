#include "RoomElements.h"
#include "../../GameObjects/Characters/Wall.h"
#include "../../GameObjects/Characters/BossWall.h"
#include "../../GameObjects/Characters/SpawnPoint.h"
#include "../../GameObjects/Characters/BossEnterWall.h"
#include "../../GameObjects/Characters/StandardEnemy.h"
#include "../../GameObjects/Characters/LootBlock.h"
#include "../../GameObjects/Characters/Chest.h"
#include <magic_enum/magic_enum.hpp>

static int thisFloor = 0;
static nlohmann::json enemyData;
static nlohmann::json chestData;

GameObject* getRoomElement(int ID, float x, float y, float w, float h)
{
	if (ID <= 0)
		return NULL;
	switch (ID)
	{
	case 1:
		return new Wall(x - 1, y - 1, w + 2, h + 2);
		
	case 2:
		return new BossWall(x - 1, y - 1, w + 2, h + 2);
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

void setUpRoomElement(std::string path)
{
	enemyData = readJson(path + "Enemies.json");
	chestData = readJson(path + "Chest.json");
}

void setUpFloor(int floor)
{
}



GameObject* getEnemy(EnemiesID ID)
{
	auto name = magic_enum::enum_name(ID);
	const char* dataName = name.data();
	switch (ID)
	{
	case EnemiesID::Goblin:
	case EnemiesID::Skeletron:
	case EnemiesID::Slime:
		return new StandardEnemy(dataName, enemyData, thisFloor);
	default:
		return new StandardEnemy(dataName, enemyData, thisFloor);
		break;
	}
	return nullptr;
}

GameObject* getEnemy(int ID, Rectangle pos)
{
	GameObject* gm = getEnemy((EnemiesID)ID);
	if (!gm)
		return nullptr;
	gm->setPos(getMidlePoint(pos));
	return gm;
}

GameObject* getChest(int ID, Rectangle pos)
{
	if (ID < 0)
		return nullptr;
	
	return new Chest(pos, ID);
}

GameObject* getObject(int ID, Rectangle pos)
{
	if (ID < 0)
		return nullptr;
	switch (ID)
	{
	case 0:
		return new LootBlock(pos.x, pos.y);
	default:
		break;
	}
	return nullptr;
}