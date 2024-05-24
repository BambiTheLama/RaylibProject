#include "Room.h"
#include "RoomElements.h"

Room::Room(int ID, int blocks[roomSize][roomSize])
{
	this->ID = ID;
	if (blocks)
	{
		for (int i = 0; i < roomSize; i++)
			for (int j = 0; j < roomSize; j++)
				blockID[i][j] = blocks[i][j];
	}
}

void Room::addObject(GameObject* gm)
{
	objects.push_back(gm);
}

RoomData Room::createRoomData()
{
	RoomData data;
	data.ID = ID;
	for (int i = 0; i < roomSize; i++)
	{
		data.up.push_back(getRoomType(blockID[0][i]));
		data.down.push_back(getRoomType(blockID[roomSize - 1][i]));
		data.left.push_back(getRoomType(blockID[i][0]));
		data.right.push_back(getRoomType(blockID[i][roomSize - 1]));
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


Room getRoom(int ID)
{
	int blocks[roomSize][roomSize];
	for (int i = 0; i < roomSize; i++)
		for (int j = 0; j < roomSize; j++)
			blocks[i][j] = 0;
	switch (ID)
	{
	case 0:
		break;
	case 1:
		for (int i = 0; i < roomSize; i++)
			for (int j = 2; j < roomSize - 2; j++)
				blocks[i][j] = 1;
		break;
	case 2:
		for (int i = 1; i < roomSize-1; i++)
			for (int j = 3; j < roomSize - 3; j++)
				blocks[i][j] = 1;
		break;
	case 3:
		for (int i = 0; i < roomSize; i++)
			for (int j = i; j < roomSize; j++)
				blocks[i][j] = 1;
		break;
	case 4:
		for (int i = 0; i < roomSize; i++)
			for (int j = 0; j < roomSize - i; j++)
				blocks[i][j] = 1;
		break;
	case 5:
		for (int i = 0; i < roomSize; i++)
			for (int j = i; j < roomSize; j++)
				blocks[j][i] = 1;
		break;
	case 6:
		for (int i = 0; i < roomSize; i++)
			for (int j = 0; j < roomSize - i; j++)
				blocks[j][i] = 1;
		break;
	case 7:
		for (int i = 0; i < roomSize; i++)
			for (int j = 0; j < roomSize; j++)
				blocks[i][j] = 1;
		break;
	default:
		break;
	}
	return Room(ID, blocks);

}