#pragma once
#include <vector>
#include "Dir.h"
#include "BlockType.h"
#include "RoomType.h"

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