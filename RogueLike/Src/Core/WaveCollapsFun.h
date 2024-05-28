#pragma once
#include <vector>

enum class BlockType :char
{
	NON, Wall, PlayerSpawnPoint, ChestSpawnPoint, EnemySpawnPoint, LootSpawnPoint, BossSpawnPoint
};

enum class Dir :char
{
	Up, Down, Left, Right, NON
};
enum class RoomType
{
	Normal, Boss, Special
};
struct RoomData {
	int ID = -1;
	char rotate = 0;
	RoomType type;
	std::vector<BlockType> up;
	std::vector<BlockType> down;
	std::vector<BlockType> left;
	std::vector<BlockType> right;
	std::vector<int> posibleRoom;

	bool isMaching(Dir dir, std::vector<BlockType> blocks);
};

struct FloorRooms {
	std::vector<RoomData> standardsRooms;
	std::vector<RoomData> specialRooms;
	std::vector<std::vector<RoomData>> bossRoom;
};

std::vector<std::vector<RoomData>> generareFloor(int w, int h, FloorRooms &floorRooms);

Dir swapDir(Dir d);