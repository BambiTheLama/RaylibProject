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

void DrawSegmentLine(Vector2 start, Vector2 dir, float lineSize, float frame, float range, int segments, Color color);

void DrawFrameRounded(Rectangle pos, Color frameColor = BLUE, Color outlineColor = BLACK);

void DrawFrameRec(Rectangle pos, Color frameColor = BLUE, Color outlineColor = BLACK);

float getFrameBolder();

Rectangle RectangleIncreasSize(Rectangle rec, float v);

Rectangle RectangleDecreasSize(Rectangle rec, float v);

float RectangleDistance(Rectangle r1, Rectangle r2);

void startOutLineShader();

Rectangle moveRectangeBy(Rectangle pos, Vector2 moveBy);

Vector2 getMidlePoint(Rectangle rec);

Vector2 randVector2();

Color mixColor(Color c1, Color c2, float procent);

Vector2 DirFromAngle(float angle);