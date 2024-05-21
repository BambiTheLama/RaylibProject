#pragma once
#include "raylib.h"

namespace MyFont {

	void SetUpFont();

	void ClearFont();

	void DrawText(const char* text, int x, int y, int size, Color color);

	Vector2 TextSize(const char* text, int size, int spacing);

	void DrawTextWithOutline(const char* text, int x, int y, int fontSize, Color textColor, Color outlineColor);

	int getFontSize();
}
