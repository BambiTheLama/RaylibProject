#include "Font.h"


namespace MyFont
{

	static Font diffFont;

	void SetUpFont()
	{
		diffFont = LoadFont("Res/PatrickHand.ttf");
	}

	void ClearFont()
	{
		UnloadFont(diffFont);
	}

	void DrawText(const char* text, float x, float y, float size, Color color)
	{
		DrawTextPro(diffFont, text, { (float)x,(float)y }, { 0.0f,0.0f }, 0.0f, size, 0.0f, color);
	}
	Vector2 TextSize(const char* text, float size, float spacing)
	{
		return MeasureTextEx(diffFont, text, size, spacing);
	}

	void DrawTextWithOutline(const char* text, float x, float y, float fontSize, Color textColor, Color outlineColor) {
		outlineColor.a = outlineColor.a / 9 + (outlineColor.a % 9 > 0 ? 1 : 0);
		for (int ox = -OutlineSpacing; ox <= OutlineSpacing; ox += 2) {
			for (int oy = -OutlineSpacing; oy <= OutlineSpacing; oy += 2) {
				MyFont::DrawText(text, x + ox, y + oy, fontSize, outlineColor);
			}
		}
		MyFont::DrawText(text, x, y, fontSize, textColor);
	}

	float getFontSize()
	{
		return 64.0f;
	}
}