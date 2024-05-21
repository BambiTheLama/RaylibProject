#include "Engine.h"
#include "raylib.h"
#include "GameScene.h"
#include "../Font.h"

Engine::Engine() {
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MyFont::SetUpFont();
    s = new GameScene();
    s->start();
    while (!WindowShouldClose() && s) {
        float deltaTime = GetFrameTime();
        if (deltaTime > 0.2f)
            deltaTime = 0.2f;
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
