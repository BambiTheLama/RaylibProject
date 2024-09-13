#include "Engine.h"
#include "raylib.hpp"
#include "GameScene.h"
#include "RoomEdytor.h"
#include "../Font.h"
#include <time.h>
#include <fstream>
#include "Controller/TextureController.h"
#include "Controller/ShaderController.h"
#include <string>

Engine::Engine() {
    srand((unsigned int)time(NULL));
    srand(69);
    const int screenWidth = 1600;
    const int screenHeight = 900;
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Roguelike");

    //ToggleFullscreen();

    TextureController::setUpTexture("Res/");
    ShaderController::setUpShader("Res/Shader/");
    
    SetTargetFPS(60);
    MyFont::SetUpFont();
    setScene(new GameScene());
    std::string text = TextFormat("%d", (int)(1.0f / 1.0f));
    float timer = 0.1f;
    while (!WindowShouldClose() && s) {

        if (IsKeyPressed(KEY_F1))
        {
            clearScene();
            setScene(new GameScene());
        }
        if (IsKeyPressed(KEY_F2))
        {
            clearScene();
            setScene(new RoomEdytor());
        }


        float deltaTime = fminf(GetFrameTime(), 1.0f / 30.0f);

        if (IsKeyDown(KEY_LEFT_SHIFT))
            deltaTime /= 20.0f;


        s->update(deltaTime);
        BeginDrawing();

        ClearBackground(GetColor(0x333377ff));
        s->draw();
        timer -= GetFrameTime();
        if (timer <= 0.0f)
        {
            text = TextFormat("%d FPS", (int)(1.0f / GetFrameTime()));
            timer = 0.1f;
        }
        //MyFont::DrawTextWithOutline(text.c_str(), 0, 0, 32, GREEN, BLACK);
        DrawFPS(0, 0);
        EndDrawing();
    }
    if (s)
        delete s;
    MyFont::ClearFont();
    TextureController::clearTextures();
    ShaderController::clearShaders();
    CloseWindow();
}

void Engine::setScene(Scene *s) {
    if (!s)
        return;
    if (this->s)
    {
        this->s->onDestroy();
        delete this->s;
    }


    this->s = s;
    s->start();
}
void Engine::clearScene()
{
    if (!s)
        return;
    delete s;
    s = nullptr;
}