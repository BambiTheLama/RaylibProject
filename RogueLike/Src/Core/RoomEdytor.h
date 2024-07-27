#pragma once
#include "Scene.h"
#include <vector>
#include "Floor/Room.h"
#include "raylib.hpp"

class RoomEdytor :
    public Scene
{
    std::string path;
    int ID = 0;
    RoomType type = RoomType::Normal;
    int bossW = 1;
    int bossH = 1;
    std::vector<std::vector<int>> room;
    std::vector<std::vector<std::vector<int>>> normalRoom;
    std::vector<std::vector<std::vector<int>>> bossRoom;
    std::vector<std::vector<std::vector<int>>> specialRoom;
    Vector2 startRoom = { 100.0f,100.0f };
    Vector2 sizeRoom = { 32.0f, 32.0f };
    int usingBlock = 0;
public:
    RoomEdytor();

    ~RoomEdytor();

    void start();

    void onDestroy(){}

    void update(float deltaTime);

    void save();

    void readFromFile();

    void saveRoomsAsPng(std::string path);

    void readRoomsFormPng(std::string path);

    void saveAsPng(RoomType type, std::string name);

    void readFormPng(RoomType type, std::string name);

    void load();

    std::vector<std::vector<int>> createRoom();

    void draw();
};

Color getColorFromType(int i);

Color getColorFromType(BlockType type);

BlockType getRoomFromColor(Color c);

int getRoomElementFromColor(Color c);