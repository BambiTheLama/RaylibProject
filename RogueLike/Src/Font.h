#pragma once
#include "raylib.hpp"

namespace MyFont {
#define OutlineSpacing 2
	void SetUpFont();

	void ClearFont();

	void DrawText(const char* text, float x, float y, float size, Color color = BLACK, Vector2 rotationPoint = { 0.0f,0.0f }, float angle = 0.0f);

	Vector2 TextSize(const char* text, float size, float spacing);

	void DrawTextWithOutline(const char* text, float x, float y, float fontSize, Color textColor, Color outlineColor, Vector2 rotationPoint = { 0.0f,0.0f }, float angle = 0.0f);

	float getFontSize();
}
