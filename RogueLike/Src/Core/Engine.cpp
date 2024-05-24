#include "Engine.h"
#include "raylib.hpp"
#include "GameScene.h"
#include "RoomEdytor.h"
#include "../Font.h"
#include <time.h>

Engine::Engine() {
    srand(time(NULL));
    //srand(69);
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    MyFont::SetUpFont();
    setScene(new GameScene());
    while (!WindowShouldClose() && s) {

        if(IsKeyPressed(KEY_F1))
            setScene(new GameScene());
        if (IsKeyPressed(KEY_F2))
            setScene(new RoomEdytor());


        float deltaTime = GetFrameTime();
        if (deltaTime > 1.0f / 60.0f)
            deltaTime = 1.0f / 60.0f;
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
