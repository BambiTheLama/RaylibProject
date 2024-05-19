#include "Engine.h"
#include "raylib.h"
#include "GameScene.h"

Engine::Engine() {
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    s = new GameScene();
    s->start();
    while (!WindowShouldClose()) {
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
    CloseWindow();
}

void Engine::setScene(Scene *s) {
    if (!s)
        return;
    delete this->s;
    s->start();
    this->s = s;
}
