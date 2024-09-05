#pragma once
#include "raylib.h"
#include "vector"
#include "../../Core/Controller/TextureController.h"

struct Particle {
    Vector2 pos = { .0f, .0f };
    Vector2 dir = { .0f, .0f };
    float size = .0f;
    float deltaSize = 0.0f;
    float speed = .0f;
    float acceleration = .0f;
    float angle = 0.0f;
    float deltaAngle = 0.0f;
    float timer = .1f;
    float timerMax = .1f;
    std::vector<Color> colors = { {255,255,0,255},{255,0,0,160},{0,0,0,60},{80,80,80,0} };

    void update(float deltaTime);

    Color getColor();

    void draw(TextureController& texture, float scale = 1.0f);
};
