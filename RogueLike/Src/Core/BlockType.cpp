#include "BlockType.h"
#include <map>


static std::map<BlockType, int> roomColor = {
	{BlockType::NON				,	0xffffffff},
	{BlockType::Wall			,	0xff0000ff},
	{BlockType::BossWall		,	0xff2222ff},
	{BlockType::PlayerSpawnPoint,	0x00ff00ff},
	{BlockType::ChestSpawnPoint	,	0xffff00ff},
	{BlockType::EnemySpawnPoint ,	0xffaaffff},
	{BlockType::ElitEnemySpawn	,	0xff00ffff},
	{BlockType::LootSpawnPoint	,	0xff9900ff},
	{BlockType::BossEnterWall	,	0xaa0000ff},
	{BlockType::BossSpawnPoint	,	0x000000ff},
	{BlockType::Torch           ,   0x999999ff},
	{BlockType::ShopKeeper		,	0x00ff99ff}	

};

bool isWallType(BlockType type)
{
	switch (type)
	{
	case BlockType::Wall:
	case BlockType::BossWall:
	case BlockType::BossEnterWall:
		return true;
	default:
		break;
	}
	return false;
}

Color getColorFromType(int i)
{
	return getColorFromType(getRoomElementType(i));
}

Color getColorFromType(BlockType type)
{
	auto find = roomColor.find(type);
	if (find != roomColor.end())
	{
		return GetColor(find->second);
	}
	return WHITE;
}

BlockType getRoomFromColor(Color c)
{
	int color = ColorToInt(c);
	for (auto r : roomColor)
	{
		if (r.second == color)
			return r.first;
	}
	return BlockType::NON;
}

int getRoomElementFromColor(Color c)
{
	return getRoomElementID(getRoomFromColor(c));
}


BlockType getRoomElementType(int ID)
{
	return (BlockType)ID;
}

int getRoomElementID(BlockType type)
{
	return (int)type;
}