#include "RoomEdytor.h"
#include "raylib.hpp"
#include <fstream>
#include <json.hpp>
#include "Floor/RoomElements.h"
#include "../Font.h"



RoomEdytor::RoomEdytor()
{
	//path = "Res/Rooms.json";
	//readFromFile();
	readRoomsFormPng("Res/Rooms/");
	
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
	saveRoomsAsPng("Res/Rooms/");
	
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
		ID += (int)m;
		if (ID < 0)
			ID = 0;
		else switch (type)
		{
		case RoomType::Normal:
			if (ID >= (int)normalRoom.size())
				ID = (int)normalRoom.size() - 1;
			break;
		case RoomType::Boss:
			if (ID >= (int)bossRoom.size())
				ID = (int)bossRoom.size() - 1;
			break;
		case RoomType::Special:
			if (ID >= (int)specialRoom.size())
				ID = (int)specialRoom.size() - 1;
			break;
		default:
			break;
		}

	}
	else
	{

		usingBlock += (int)m;
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
		int x = (int)(mouse.x / sizeRoom.x);
		int y = (int)(mouse.y / sizeRoom.y);
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

void RoomEdytor::readFromFile()
{
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



}

void RoomEdytor::saveRoomsAsPng(std::string path)
{
	saveAsPng(RoomType::Boss, path + "Boss.png");
	saveAsPng(RoomType::Normal, path + "Normal.png");
	saveAsPng(RoomType::Special, path + "Special.png");
}

void RoomEdytor::readRoomsFormPng(std::string path)
{
	readFormPng(RoomType::Boss, path + "Boss.png");
	readFormPng(RoomType::Normal, path + "Normal.png");
	readFormPng(RoomType::Special, path + "Special.png");
}

void drawRoom(int x, int y,std::vector<std::vector<int>> rooms)
{
	for (int i = 0; i < rooms.size(); i++)
		for (int j = 0; j < rooms[i].size(); j++)
			DrawPixel(x + j, y + i, getColorFromType(rooms[i][j]));
}

void RoomEdytor::saveAsPng(RoomType type, std::string name)
{
	RenderTexture2D texture;
	texture.id = -1;
	switch (type)
	{
	case RoomType::Normal:
		texture = LoadRenderTexture(roomSize * (int)normalRoom.size(), roomSize);
		BeginTextureMode(texture);
		for (int i = 0; i < normalRoom.size(); i++)
		{
			drawRoom(i * roomSize, 0, normalRoom[i]);
		}
		EndTextureMode();
		break;
	case RoomType::Boss:
		texture = LoadRenderTexture(roomSize * bossW, roomSize * bossH);
		BeginTextureMode(texture);
		for (int i = 0; i < bossRoom.size(); i++)
		{
			drawRoom((i % bossW) * roomSize, (i / bossW) * roomSize, bossRoom[i]);
		}
		EndTextureMode();
		break;
	case RoomType::Special:
		texture = LoadRenderTexture(roomSize * (int)specialRoom.size(), roomSize);
		BeginTextureMode(texture);
		for (int i = 0; i < specialRoom.size(); i++)
		{
			drawRoom(i * roomSize, 0, specialRoom[i]);
		}
		EndTextureMode();
		break;
	default:
		break;
	}
	if (texture.id < 0)
		return;
	RenderTexture2D texture2=LoadRenderTexture(texture.texture.width,texture.texture.height);
	BeginTextureMode(texture2);
	DrawTexture(texture.texture, 0, 0, WHITE);
	EndTextureMode();
	Image image = LoadImageFromTexture(texture2.texture);
	if (ExportImage(image, name.c_str()))
		printf("[INFO]: Saved %s\n", name.c_str());
	UnloadImage(image);
	UnloadRenderTexture(texture);
	UnloadRenderTexture(texture2);
}


void RoomEdytor::readFormPng(RoomType type, std::string name)
{
	std::vector<std::vector<std::vector<int>>> rooms = readFromPng(name);
	switch (type)
	{
	case RoomType::Normal:
		normalRoom = rooms;
		break;
	case RoomType::Boss:
		bossRoom = rooms;
		{
			Image image = LoadImage(name.c_str());
			bossH = image.width / roomSize;
			bossW = image.height / roomSize;
			UnloadImage(image);
		}
		break;
	case RoomType::Special:
		specialRoom = rooms;
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
			Color c = getColorFromType(getRoomElementType(room[y][x]));

			DrawFrameRec(pos, c, BLACK);
			MyFont::DrawTextWithOutline(TextFormat("%d", room[y][x]), pos.x, pos.y, 32, WHITE, BLACK);
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
	MyFont::DrawTextWithOutline(TextFormat("UsingBlock = %d\nRoomID = %d\nRoomType = [%s]", usingBlock,ID, roomName.c_str()), 0, 10, 32, WHITE, BLACK);

	MyFont::DrawTextWithOutline(TextFormat("Boss = %d  [%dx%d]", bossRoom.size(),bossW,bossH), 1000, 200, 32, WHITE, BLACK);
	MyFont::DrawTextWithOutline(TextFormat("Special = %d", specialRoom.size()), 1000, 250, 32, WHITE, BLACK);
	MyFont::DrawTextWithOutline(TextFormat("Normal = %d", normalRoom.size()), 1000, 300, 32, WHITE, BLACK);
	DrawRectangle(950, 200, 32, 32, RED);
	DrawRectangle(950, 250, 32, 32, RED);
	DrawRectangle(950, 300, 32, 32, RED);

}

