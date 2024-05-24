#pragma once
#include <vector>
#include "../WaveCollapsFun.h"
#include <json.hpp>

#define roomSize 8
#define tileW 32
#define tileH 32
#define roomW (roomSize*tileW)
#define roomH (roomSize*tileH)

class GameObject;

class Room
{
	int ID;
	int blockID[roomSize][roomSize];
	std::vector<GameObject*> objects;
	RoomType type;
public:
	Room(int ID, RoomType type, int blocks[roomSize][roomSize]);

	void addObject(GameObject* gm);

	RoomData createRoomData();

	int getBlockID(int x, int y);

	std::vector<GameObject*> getObjects();

	int getID() { return ID; }
};

void loadRooms(nlohmann::json& j);

Room getRoom(RoomType type,int ID);

int getRoomSize(RoomType type);

struct Vec2 {
	int x, y;
};

Vec2 getBossRoomSize();
