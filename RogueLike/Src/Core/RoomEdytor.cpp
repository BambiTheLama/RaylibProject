#include "RoomEdytor.h"
#include "raylib.hpp"
#include <fstream>
#include <json.hpp>
#include "Floor/RoomElements.h"
#include "../Font.h"

RoomEdytor::RoomEdytor()
{
	path = "Res/Rooms.json";
	std::ifstream reader(path.c_str());
	nlohmann::json j;
	if (reader.is_open())
	{
		reader >> j;
		reader.close();
	}
	else
	{
		return;
	}
	if (j.contains("BOSSROOMSIZE"))
	{
		bossW = j["BOSSROOMSIZE"][0];
		bossH = j["BOSSROOMSIZE"][1];
	}

	if (j.contains("BOSSROOM"))
	{




		for (int i = 0; i < j["BOSSROOM"].size(); i++)
		{
			std::vector<std::vector<int>> blocks;
			loadRoom(blocks, j["BOSSROOM"][i]);
			bossRoom.push_back(blocks);
		}

	}
	if (j.contains("SPECIALROOM"))
	{
		for (int i = 0; i < j["SPECIALROOM"].size(); i++)
		{
			std::vector<std::vector<int>> blocks;
			loadRoom(blocks, j["SPECIALROOM"][i]);
			specialRoom.push_back(blocks);
		}
	}
	if (j.contains("ROOM"))
	{
		for (int i = 0; i < j["ROOM"].size(); i++)
		{
			std::vector<std::vector<int>> blocks;
			loadRoom(blocks, j["ROOM"][i]);
			normalRoom.push_back(blocks);
		}
	}


	room = createRoom();
}

RoomEdytor::~RoomEdytor()
{
	nlohmann::json j;
	j["BOSSROOMSIZE"][0] = bossW;
	j["BOSSROOMSIZE"][1] = bossH;
	for (int i = 0; i < bossRoom.size(); i++)
	{
		for (int y = 0; y < roomSize; y++)
			for (int x = 0; x < roomSize; x++)
				j["BOSSROOM"][i][y][x] = bossRoom[i][y][x];
	}
	

	for (int i = 0; i < specialRoom.size(); i++)
	{
		for (int y = 0; y < roomSize; y++)
			for (int x = 0; x < roomSize; x++)
				j["SPECIALROOM"][i][y][x] = specialRoom[i][y][x];
	}
	for (int i = 0; i < normalRoom.size(); i++)
	{
		for (int y = 0; y < roomSize; y++)
			for (int x = 0; x < roomSize; x++)
				j["ROOM"][i][y][x] = normalRoom[i][y][x];
	}


	std::ofstream writer(path.c_str());


	writer << j;
	writer.close();

	
}

void RoomEdytor::start()
{

}

void RoomEdytor::update(float deltaTime)
{
	float m = GetMouseWheelMove();
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		if (IsKeyDown(KEY_TAB))
			ID = 1000;
		save();
		ID += m;
		if (ID < 0)
			ID = 0;
		else switch (type)
		{
		case RoomType::Normal:
			if (ID >= normalRoom.size())
				ID = normalRoom.size() - 1;
			break;
		case RoomType::Boss:
			if (ID >= bossRoom.size())
				ID = bossRoom.size() - 1;
			break;
		case RoomType::Special:
			if (ID >= specialRoom.size())
				ID = specialRoom.size() - 1;
			break;
		default:
			break;
		}

	}
	else
	{

		usingBlock += m;
		if (usingBlock < 0)
			usingBlock = 0;
		else if (usingBlock > 100)
			usingBlock = 100;
	}


	Rectangle pos= { startRoom.x ,startRoom.y,sizeRoom.x*roomSize,sizeRoom.y * roomSize };
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), pos))
	{
		Vector2 mouse = GetMousePosition();
		mouse.x -= startRoom.x;
		mouse.y -= startRoom.y;
		int x = mouse.x / sizeRoom.x;
		int y = mouse.y / sizeRoom.y;
		room[y][x] = usingBlock;
		save();
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(GetMousePosition(), { 1000,200,64,32 }))
		{
			save();
			type = RoomType::Boss;

		}
		else if (CheckCollisionPointRec(GetMousePosition(), { 1000,250,64,32 }))
		{
			save();
			type = RoomType::Special;
		}
		else if (CheckCollisionPointRec(GetMousePosition(), { 1000,300,64,32 }))
		{
			save();
			type = RoomType::Normal;
		}

	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(GetMousePosition(), { 950,200,32,32 }))
		{
			bossRoom.push_back(createRoom());
		}
		else if (CheckCollisionPointRec(GetMousePosition(), { 950,250,32,32 }))
		{
			specialRoom.push_back(createRoom());
		}
		else if (CheckCollisionPointRec(GetMousePosition(), { 950,300,32,32 }))
		{

			normalRoom.push_back(createRoom());
		}
	}

	if (IsKeyPressed(KEY_DELETE))
	{
		if (ID >= 0)
		switch (type)
		{
		case RoomType::Normal:
			if (normalRoom.size() > ID)
				normalRoom.erase(normalRoom.begin() + ID);
			break;
		case RoomType::Boss:
			if (bossRoom.size() > ID)
				bossRoom.erase(bossRoom.begin() + ID);
			break;
		case RoomType::Special:
			if (specialRoom.size() > ID)
				specialRoom.erase(specialRoom.begin() + ID);
			break;
		default:
			break;
		}
	}
	if (IsKeyPressed(KEY_UP))
	{
		bossH++;
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		bossH--;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		bossW++;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		bossW--;
	}
	if (bossH < 0)
		bossH = 0;
	if (bossW < 0)
		bossW = 0;
	
	load();
}

void RoomEdytor::save()
{
	if (ID < 0)
		return;
	switch (type)
	{
	case RoomType::Normal:
		if (ID < normalRoom.size())
		{
			normalRoom[ID] = room;
		}
		break;
	case RoomType::Boss:
		if (ID < bossRoom.size())
		{
			bossRoom[ID] = room;
		}
		break;
	case RoomType::Special:
		if (ID < specialRoom.size())
		{
			specialRoom[ID] = room;
		}
		break;
	default:
		break;
	}
}

void RoomEdytor::load()
{
	if (ID < 0)
		return;
	switch (type)
	{
	case RoomType::Normal:
		if (ID < normalRoom.size())
		{
			room = normalRoom[ID];
		}
		break;
	case RoomType::Boss:
		if (ID < bossRoom.size())
		{
			room = bossRoom[ID];
		}
		break;
	case RoomType::Special:
		if (ID < specialRoom.size())
		{
			room = specialRoom[ID];
		}
		break;
	default:
		break;
	}
}

std::vector<std::vector<int>> RoomEdytor::createRoom()
{
	std::vector<std::vector<int>> tmp;
	for (int y = 0; y < roomSize; y++)
	{
		std::vector<int> r;
		for (int x = 0; x < roomSize; x++)
			r.push_back(0);
		tmp.push_back(r);
	}
	return tmp;
}

void RoomEdytor::draw()
{
	for(int x=0;x<roomSize;x++)
		for (int y = 0; y < roomSize; y++)
		{
			Rectangle pos = { startRoom.x + x * sizeRoom.x,startRoom.y + y * sizeRoom.y,sizeRoom.x,sizeRoom.y };
			Color c = WHITE;
			switch (getRoomElementType(room[y][x]))
			{
			case BlockType::NON:
				c = WHITE;
				break;
			case BlockType::Wall:
				c = RED;
				break;
			case BlockType::PlayerSpawnPoint:
				c = GREEN;
				break;
			case BlockType::ChestSpawnPoint:
				c = YELLOW;
				break;
			case BlockType::EnemySpawnPoint:
				c = PINK;
				break;
			case BlockType::LootSpawnPoint:
				c = ORANGE;
				break;
			case BlockType::BossSpawnPoint:
				c = PURPLE;
				break;
			case BlockType::BossEnterWall:
				c = BLACK;
				break;
			case BlockType::ElitEnemySpawn:
				c = GetColor(0xff00ffff);
				break;
			default:
				break;
			}
			DrawRectangleRec(pos, c);
			MyFont::DrawTextWithOutline(TextFormat("%d", room[y][x]), pos.x, pos.y, 32, WHITE, BLACK);
			DrawRectangleLinesEx(pos, 2, BLACK);
		}
	std::string roomName="NON";
	switch (type)
	{
	case RoomType::Normal:
		roomName = "Normal";
		break;
	case RoomType::Boss:
		roomName = "Boss";
		break;
	case RoomType::Special:
		roomName = "Special";
		break;
	default:
		break;
	}
	MyFont::DrawTextWithOutline(TextFormat("UsingBlock = %d\n\nRoomID = %d\n\nRoomType = [%s]", usingBlock,ID, roomName.c_str()), 0, 10, 32, WHITE, BLACK);

	MyFont::DrawTextWithOutline(TextFormat("Boss = %d  [%dx%d]", bossRoom.size(),bossW,bossH), 1000, 200, 32, WHITE, BLACK);
	MyFont::DrawTextWithOutline(TextFormat("Special = %d", specialRoom.size()), 1000, 250, 32, WHITE, BLACK);
	MyFont::DrawTextWithOutline(TextFormat("Normal = %d", normalRoom.size()), 1000, 300, 32, WHITE, BLACK);
	DrawRectangle(950, 200, 32, 32, RED);
	DrawRectangle(950, 250, 32, 32, RED);
	DrawRectangle(950, 300, 32, 32, RED);

}