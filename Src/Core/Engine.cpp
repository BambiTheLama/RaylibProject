//
// Created by Szymek on 14.05.2024.
//

#include "Engine.h"
#include "raylib.h"
#include "GameScene.h"
Engine::Engine()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    s = new GameScene();
    s->start();
    while (!WindowShouldClose())
    {
        s->update(GetFrameTime());
        BeginDrawing();
        ClearBackground(RAYWHITE);
        s->draw();
        DrawFPS(0,0);
        EndDrawing();


    }
    CloseWindow();
}

void Engine::setScene(Scene* s){
    if(!s)
        return;
    delete this->s;
    s->start();
    this->s=s;
}