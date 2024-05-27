#include "Room.h"
#include "RoomElements.h"

Vec2 bossRoomSize = { 0,0 };
static std::vector<Room> normalRooms;
static std::vector<Room> specialRooms;
static std::vector<Room> bossRooms;

void loadRoom(int blocks[roomSize][roomSize], nlohmann::json& j)
{
	for (int y = 0; y < j.size() && y < roomSize; y++)
		for (int x = 0; x < j[y].size() && x < roomSize; x++)
			blocks[y][x] = j[y][x];
}

void loadRoom(std::vector<std::vector<int>> &blocks, nlohmann::json& j)
{
	blocks.clear();
	for (int y = 0; y < j.size(); y++)
	{
		std::vector<int> data;
		for (int x = 0; x < j[y].size(); x++)
		{
			data.push_back(j[y][x]);
		}
		for (int x = j[y].size(); x < roomSize; x++)
		{
			data.push_back(0);
		}
		blocks.push_back(data);
	}
	for (int y = j.size(); y < roomSize; y++)
	{
		std::vector<int> data;
		for (int x = 0; x < roomSize; x++)
		{
			data.push_back(0);
		}
		blocks.push_back(data);
	}

}

void loadRooms(nlohmann::json &j) {
	bossRooms.clear();
	normalRooms.clear();
	specialRooms.clear();
	int blocks[roomSize][roomSize];
	if (j.contains("BOSSROOMSIZE"))
	{
		bossRoomSize.x = j["BOSSROOMSIZE"][0];
		bossRoomSize.y = j["BOSSROOMSIZE"][1];
	}

	if (j.contains("BOSSROOM"))
	{

		for (int i = 0; i < j["BOSSROOM"].size(); i++)
		{
			loadRoom(blocks, j["BOSSROOM"][i]);
			bossRooms.push_back(Room(i,RoomType::Boss, blocks));
		}

	}
	if (j.contains("SPECIALROOM"))
	{
		for (int i = 0; i < j["SPECIALROOM"].size(); i++)
		{
			loadRoom(blocks, j["SPECIALROOM"][i]);
			specialRooms.push_back(Room(i, RoomType::Special, blocks));
		}
	}
	if (j.contains("ROOM"))
	{
		for (int i = 0; i < j["ROOM"].size(); i++)
		{
			loadRoom(blocks, j["ROOM"][i]);
			normalRooms.push_back(Room(i, RoomType::Normal, blocks));
		}
	}
}

Room::Room(int ID, RoomType type, int blocks[roomSize][roomSize])
{
	this->ID = ID;
	if (blocks)
	{
		for (int i = 0; i < roomSize; i++)
			for (int j = 0; j < roomSize; j++)
				blockID[i][j] = blocks[i][j];
	}
	this->type = type;
}

void Room::addObject(GameObject* gm)
{
	objects.push_back(gm);
}

RoomData Room::createRoomData()
{
	RoomData data;
	data.type = type;
	data.ID = ID;
	for (int i = 0; i < roomSize; i++)
	{
		data.up.push_back(getRoomElementType(blockID[0][i]));
		data.down.push_back(getRoomElementType(blockID[roomSize - 1][i]));
		data.left.push_back(getRoomElementType(blockID[i][0]));
		data.right.push_back(getRoomElementType(blockID[i][roomSize - 1]));
	}

	return data;
}

int Room::getBlockID(int x, int y)
{
	if (x < 0 || y < 0 || x >= roomSize || y >= roomSize)
		return -1;
	return blockID[y][x];
}

std::vector<GameObject*> Room::getObjects()
{
	return objects;
}


Room getRoom(RoomType type, int ID)
{
	if (ID >= 0)
	switch (type)
	{
	case RoomType::Normal:
		if (ID < normalRooms.size())
			return normalRooms[ID];
		break;
	case RoomType::Boss:
		if (ID < bossRooms.size())
			return bossRooms[ID];
		break;
	case RoomType::Special:
		if (ID < specialRooms.size())
			return specialRooms[ID];
		break;
	}
	int blocks[roomSize][roomSize];
	for (int i = 0; i < roomSize; i++)
		for (int j = 0; j < roomSize; j++)
			blocks[i][j] = 0;
	return Room(ID, RoomType::Normal, blocks);
}

int getRoomSize(RoomType type)
{
	switch (type)
	{
	case RoomType::Normal:
		return normalRooms.size();
	case RoomType::Boss:
		return bossRooms.size();
	case RoomType::Special:
		return specialRooms.size();
	}
	return 0;
}

Vec2 getBossRoomSize()
{
	return bossRoomSize;
}