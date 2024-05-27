#include "WaveCollapsFun.h"
#include <algorithm>

bool RoomData::isMaching(Dir dir, std::vector<BlockType> blocks)
{
	if (ID < 0)
		return true;
	std::vector<BlockType> thisBlocks;
	switch (dir) {
	case Dir::Up:
		thisBlocks = up;
		break;
	case Dir::Down:
		thisBlocks = down;
		break;
	case Dir::Right:
		thisBlocks = right;
		break;
	case Dir::Left:
		thisBlocks = left;
		break;
	default:
		return false;
	}

	if (thisBlocks.size() <= 0)
		return false;

	if (blocks.size() < thisBlocks.size())
		return false;
	int mistakes = 0;
	for (int i = 0; i < thisBlocks.size(); i++)
		if (thisBlocks[i] != blocks[i])
			mistakes++;
	return mistakes < 3;

}

static std::vector<std::vector<RoomData>> createFloar(int w, int h)
{
	std::vector<std::vector<RoomData>>roomGrid;
	for (int y = 0; y < h; y++)
	{
		std::vector<RoomData> rooms;
		for (int x = 0; x < w; x++)
		{
			rooms.push_back(RoomData());
		}
		roomGrid.push_back(rooms);
	}
	return roomGrid;
}

static bool hasRoomsAt(std::vector<std::vector<RoomData>>& roomGrid, int x, int y)
{
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			int thisX = x + i;
			int thisY = y + j;
			if (thisX < 0 || thisX >= roomGrid[0].size() || thisY < 0 || thisY >= roomGrid.size())
				continue;
			if (roomGrid[thisY][thisX].ID >= 0)
				return false;
		}
	return true;
}

static void setBoosRoom(std::vector<std::vector<RoomData>>& roomGrid, std::vector<std::vector<RoomData>>& bossRoom)
{
	const int bossRoomSizeW = bossRoom[0].size();
	const int bossRoomSizeH = bossRoom.size();
	const int gridW = roomGrid[0].size();
	const int gridH = roomGrid.size();
	if (bossRoomSizeH <= 0 || bossRoomSizeW <= 0)
		return;
	const int x = rand() % (gridW - bossRoomSizeW);
	const int y = rand() % (gridH - bossRoomSizeH);
	for (int i = 0; i < bossRoomSizeH; i++)
		for (int j = 0; j < bossRoomSizeW; j++)
			roomGrid[y + i][x + j] = bossRoom[i][j];
}

static void setSpecialRooms(std::vector<std::vector<RoomData>>& roomGrid, std::vector<RoomData>& specialRooms)
{
	for (auto r : specialRooms)
	{
		RoomData room = r;
		int x = 0;
		int y = 0;
		do
		{
			x = rand() % roomGrid[0].size();
			y = rand() % roomGrid.size();
		} while (!hasRoomsAt(roomGrid, x, y));

		roomGrid[y][x] = room;
	}
}

static bool isPossibleRoom(std::vector<std::vector<RoomData>>& roomGrid, RoomData& room, int x, int y) {
	if (x - 1 >= 0)
		if (!roomGrid[y][x - 1].isMaching(Dir::Right, room.left))
			return false;
	if (x + 1 < roomGrid[0].size())
		if (!roomGrid[y][x + 1].isMaching(Dir::Left, room.right))
			return false;
	if (y - 1 >= 0)
		if (!roomGrid[y - 1][x].isMaching(Dir::Down, room.up))
			return false;
	if (y + 1 < roomGrid.size())
		if (!roomGrid[y + 1][x].isMaching(Dir::Up, room.down))
			return false;
	
	return true;
}

static void setPossibleRooms(std::vector<std::vector<RoomData>>& roomGrid, std::vector<RoomData>& rooms, int x, int y) {
	
	if (y < 0 || y >= roomGrid.size() || x < 0 || x >= roomGrid[0].size())
		return;
	if (roomGrid[y][x].ID >= 0)
		return;
	roomGrid[y][x].posibleRoom.clear();

	for (int i = 0; i < rooms.size(); i++)
	{
		if (isPossibleRoom(roomGrid, rooms[i], x, y))
		{
			roomGrid[y][x].posibleRoom.push_back(i);
		}
	}
}

struct Vector2 {
	int x, y;
};

static void sortRoomsToFill(std::vector<std::vector<RoomData>>& roomGrid, std::vector<Vector2>& roomsToFill)
{
	if (roomsToFill.size() <= 1)
		return;
	for (int j = 0; j < roomsToFill.size() - 1; j++)
		for (int i = 0; i < roomsToFill.size() - 1; i++)
		{
			Vector2 p1 = roomsToFill[i];
			Vector2 p2 = roomsToFill[i + 1];
			if (roomGrid[p1.y][p1.x].posibleRoom.size() < roomGrid[p2.y][p2.x].posibleRoom.size())
			{
				roomsToFill[i] = p2;
				roomsToFill[i + 1] = p1;
			}
		}
		
}

static void fillRooms(std::vector<std::vector<RoomData>>& roomGrid, std::vector<RoomData>& rooms) {
	std::vector<Vector2> roomsToFill;
	for (int y = 0; y < roomGrid.size(); y++)
		for (int x = 0; x < roomGrid[0].size(); x++)
		{
			setPossibleRooms(roomGrid, rooms, x, y);
			if (roomGrid[y][x].ID < 0) {
				roomsToFill.push_back({ x,y });
			}
		}
	sortRoomsToFill(roomGrid, roomsToFill);
	while (roomsToFill.size() > 0)
	{
		Vector2 p = roomsToFill.back();
		roomsToFill.pop_back();
		int n = roomGrid[p.y][p.x].posibleRoom.size();
		int ID = 0;
		if (n > 0)
		{
			int e = rand() % n;
			ID = roomGrid[p.y][p.x].posibleRoom[e];

		}
		else
		{

			setPossibleRooms(roomGrid, rooms, p.x, p.y);
			n = roomGrid[p.y][p.x].posibleRoom.size();
			if (n <= 0)
			{
				printf("KURWA NIE MA POOJU %d %d\n", p.x, p.y);
			}
			else
			{
				int e = rand() % n;
				ID = roomGrid[p.y][p.x].posibleRoom[e];
			}

		}
		roomGrid[p.y][p.x] = rooms[ID];
		setPossibleRooms(roomGrid, rooms, p.x - 1, p.y);
		setPossibleRooms(roomGrid, rooms, p.x + 1, p.y);
		setPossibleRooms(roomGrid, rooms, p.x, p.y - 1);
		setPossibleRooms(roomGrid, rooms, p.x, p.y + 1);
		sortRoomsToFill(roomGrid, roomsToFill);
	}
}

std::vector<std::vector<RoomData>> generareFloor(int w, int h, FloorRooms& floorRooms)
{
	std::vector<std::vector<RoomData>>roomGrid = createFloar(w, h);
	if (floorRooms.bossRoom.size() > 0)
		setBoosRoom(roomGrid, floorRooms.bossRoom);
	if (floorRooms.specialRooms.size() > 0)
		setSpecialRooms(roomGrid, floorRooms.specialRooms);
	if (floorRooms.standardsRooms.size() > 0)
		fillRooms(roomGrid, floorRooms.standardsRooms);
	
	return roomGrid;
}

Dir swapDir(Dir d)
{
	switch (d)
	{
	case Dir::Up:
		return Dir::Down;
	case Dir::Down:
		return Dir::Up;
	case Dir::Left:
		return Dir::Right;
	case Dir::Right:
		return Dir::Left;
	}
	return Dir::NON;
}