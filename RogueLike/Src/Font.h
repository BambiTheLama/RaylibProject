#pragma once
#include "raylib.hpp"
#include <vector>
#include <string>

namespace MyFont {
#define OutlineSpacing 2
	void SetUpFont();

	void ClearFont();

	std::vector<std::string> splitLines(const char* text, std::vector<Vector3>* icons = nullptr);

	void DrawText(const char* text, float x, float y, float size, Color color = BLACK, Vector2 rotationPoint = { 0.0f,0.0f }, float angle = 0.0f, bool withIcons = true);

	Vector2 TextSize(const char* text, float size, float spacing);

	void DrawTextWithOutline(const char* text, float x, float y, float fontSize, Color textColor, Color outlineColor, Vector2 rotationPoint = { 0.0f,0.0f }, float angle = 0.0f);

	float getFontSize();
}
