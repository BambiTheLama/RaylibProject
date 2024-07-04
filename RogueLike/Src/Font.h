#pragma once
#include "raylib.hpp"

namespace MyFont {

	void SetUpFont();

	void ClearFont();

	void DrawText(const char* text, float x, float y, float size, Color color);

	Vector2 TextSize(const char* text, float size, float spacing);

	void DrawTextWithOutline(const char* text, float x, float y, float fontSize, Color textColor, Color outlineColor);

	float getFontSize();
}
