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

	void DrawText(const char* text, int x, int y, int size, Color color)
	{
		DrawTextPro(diffFont, text, { (float)x,(float)y }, { 0,0 }, 0, size, 0, color);
	}
	Vector2 TextSize(const char* text, int size, int spacing)
	{
		return MeasureTextEx(diffFont, text, size, spacing);
	}

	void DrawTextWithOutline(const char* text, int x, int y, int fontSize, Color textColor, Color outlineColor) {
		for (int ox = -1; ox <= 1; ox++) {
			for (int oy = -1; oy <= 1; oy++) {
				if (ox != 0 || oy != 0) {
					MyFont::DrawText(text, x + ox, y + oy, fontSize, outlineColor);
				}
			}
			MyFont::DrawText(text, x, y, fontSize, textColor);
		}
	}

	int getFontSize()
	{
		return 64;
	}
}