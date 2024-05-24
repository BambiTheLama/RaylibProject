#pragma once
#include "Scene.h"
#include <vector>
#include "Floor/Room.h"
#include "raylib.h"

class RoomEdytor :
    public Scene
{
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

    void update(float deltaTime);

    void save();

    void load();

    std::vector<std::vector<int>> createRoom();

    void draw();
};

