#pragma once
#include <vector>
#include "../WaveCollapsFun.h"
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
public:
	Room(int ID, int blocks[roomSize][roomSize]);

	void addObject(GameObject* gm);

	RoomData createRoomData();

	int getBlockID(int x, int y);

	std::vector<GameObject*> getObjects();

	int getID() { return ID; }
};

Room getRoom(int ID);

