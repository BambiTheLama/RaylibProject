#pragma once
#include <vector>
#include "../WaveCollapsFun.h"
#include <json.hpp>

const int roomSize = 9;
const float tileW = 32.0f;
const float tileH = 32.0f;
const float roomW = (roomSize * tileW);
const float roomH = (roomSize * tileH);

class GameObject;

class Room
{
	int ID=0;
	int blockID[roomSize][roomSize];
	std::vector<GameObject*> objects;
	RoomType type;
public:
	Room(int ID, RoomType type, int blocks[roomSize][roomSize]);

	void addObject(GameObject* gm);

	RoomData createRoomData();

	int getBlockID(int x,int y);

	std::vector<GameObject*> getObjects();

	int getID() { return ID; }
};

void loadRoom(int blocks[roomSize][roomSize], nlohmann::json& j);

void loadRoom(std::vector<std::vector<int>>& blocks, nlohmann::json& j);

void loadRooms(nlohmann::json& j);

Room getRoom(RoomType type,int ID);

int getRoomSize(RoomType type);

struct Vec2 {
	int x, y;
};

Vec2 getBossRoomSize();
