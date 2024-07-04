#include "Engine.h"
#include "raylib.hpp"
#include "GameScene.h"
#include "RoomEdytor.h"
#include "../Font.h"
#include <time.h>
#include <fstream>

Engine::Engine() {
    srand((unsigned int)time(NULL));
    srand(69);
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    std::string path = "Res/Rooms.json";
    std::ifstream reader(path.c_str());
    if (reader.is_open())
    {
        nlohmann::json j;
        reader >> j;
        reader.close();
        loadRooms(j);
    }

    //SetTargetFPS(60);
    MyFont::SetUpFont();
    setScene(new GameScene());
    while (!WindowShouldClose() && s) {

        if(IsKeyPressed(KEY_F1))
            setScene(new GameScene());
        if (IsKeyPressed(KEY_F2))
            setScene(new RoomEdytor());




        float deltaTime = GetFrameTime();
        if (deltaTime > 1.0f / 30.0f)
            deltaTime = 1.0f / 30.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT))
            deltaTime = 0.001f;
        s->update(deltaTime);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        s->draw();
        DrawFPS(0, 0);
        EndDrawing();
    }
    if (s)
        delete s;
    MyFont::ClearFont();
    CloseWindow();
}

void Engine::setScene(Scene *s) {
    if (!s)
        return;
    if(this->s)
        delete this->s;

    this->s = s;
    s->start();
}
