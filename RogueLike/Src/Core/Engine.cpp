#include "Engine.h"
#include "raylib.h"
#include "GameScene.h"
#include "../Font.h"
#include <time.h>

Engine::Engine() {
    srand(time(NULL));
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    MyFont::SetUpFont();
    s = new GameScene();
    s->start();
    while (!WindowShouldClose() && s) {
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
    delete this->s;
    s->start();
    this->s = s;
}
