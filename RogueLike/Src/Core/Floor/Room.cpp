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
		for (int x = (int)j[y].size(); x < roomSize; x++)
		{
			data.push_back(0);
		}
		blocks.push_back(data);
	}
	for (int y = (int)j.size(); y < roomSize; y++)
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

void loadRoomsFromPng(std::string path) {
	bossRooms.clear();
	normalRooms.clear();
	specialRooms.clear();
	int blocks[roomSize][roomSize];
	std::vector<std::vector<std::vector<int>>> rooms;
	
	rooms = readFromPng(path + "Normal.png");
	int i = 0;
	for (auto r : rooms)
	{
		for (int y = 0; y < r.size(); y++)
		{
			for (int x = 0; x < r[0].size(); x++)
			{
				blocks[y][x] = r[y][x];
			}
		}
		normalRooms.push_back(Room(i++, RoomType::Normal, blocks));
	}
	rooms = readFromPng(path + "Special.png");
	i = 0;
	for (auto r : rooms)
	{
		for (int y = 0; y < r.size(); y++)
		{
			for (int x = 0; x < r[0].size(); x++)
			{
				blocks[y][x] = r[y][x];
			}
		}
		specialRooms.push_back(Room(i++, RoomType::Special, blocks));
	}
	rooms = readFromPng(path + "Boss.png");
	i = 0;
	for (auto r : rooms)
	{
		for (int y = 0; y < r.size(); y++)
		{
			for (int x = 0; x < r[0].size(); x++)
			{
				blocks[y][x] = r[y][x];
			}
		}
		bossRooms.push_back(Room(i++, RoomType::Boss, blocks));
	}
	Image image = LoadImage(std::string(path + "Boss.png").c_str());
	bossRoomSize.x = image.width / roomSize;
	bossRoomSize.y = image.height / roomSize;
	UnloadImage(image);

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

int Room::getBlockID(int x,int y)
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
		return (int)normalRooms.size();
	case RoomType::Boss:
		return (int)bossRooms.size();
	case RoomType::Special:
		return (int)specialRooms.size();
	}
	return 0;
}

Vec2 getBossRoomSize()
{
	return bossRoomSize;
}

std::vector<std::vector<int>> getRoom(Color* colors, int x, int y, int w, int roomSize)
{
	std::vector<std::vector<int>> room;
	for (int i = 0; i < roomSize; i++)
	{
		std::vector<int> r;
		for (int j = 0; j < roomSize; j++)
		{
			r.push_back(getRoomElementFromColor(colors[x + j + (i + y) * w]));
		}
		room.push_back(r);
	}
	return room;
}


std::vector<std::vector<std::vector<int>>> readFromPng(std::string name)
{
	Image image = LoadImage(name.c_str());
	if (!IsImageReady(image))
	{
		UnloadImage(image);
		return std::vector<std::vector<std::vector<int>>>();
	}
	Color* colors = LoadImageColors(image);
	std::vector<std::vector<std::vector<int>>> rooms;

	int w = image.width / roomSize;
	int h = image.height / roomSize;

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			rooms.push_back(getRoom(colors, j * roomSize, i * roomSize, image.width, roomSize));
		}
	UnloadImage(image);
	UnloadImageColors(colors);
	return rooms;
}