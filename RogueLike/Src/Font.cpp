#include "Font.h"
#include <sstream>
#include "Core/Controller/TextureController.h"

namespace MyFont
{

	static Font diffFont;
	static std::vector<TextureController> icons;

	void SetUpFont()
	{
		diffFont = LoadFont("Res/PatrickHand.ttf");
		icons.push_back(TextureController("Weapons/StoneSword.png"));
		icons.push_back(TextureController("Weapons/WoodSword.png"));
	}

	void ClearFont()
	{
		UnloadFont(diffFont);
		icons.clear();
	}

	int getIconID(std::string text)
	{
		int v = 0;
		for (auto c : text)
		{
			if (c >= '0' && c <= '9')
				v = (c - '0') + v * 10;
		}
		return v;
	}

	std::string removeAllIcons(std::string text, std::vector<Vector2>* icons)
	{
		const std::string str2("{Icon:");
		int toErase = 0;
		std::size_t find;
		do {
			find = text.find(str2);
			toErase = 0;
			if (find != std::string::npos) {
				for (int i = find; i < text.size(); i++)
				{
					if (text[i] == '}')
					{
						toErase = i - find + 1;
						break;
					}
				}
				std::size_t endOfIcon = find + toErase;
				if (toErase > 0)
				{
					if (icons)
					{
						icons->push_back({ (float)getIconID(text.substr(find,toErase)), (float)find });
					}
					text = text.substr(0, find) + std::string("     ") + text.substr(endOfIcon, text.size() - endOfIcon);
				}

			}

		} while (toErase > 0);
		return text;
	}

	std::vector<std::string> splitLines(const char* text, std::vector<Vector3>* icons) {
		std::istringstream stream = std::istringstream(std::string(text));
		std::vector<std::string> lines;
		std::string line;
		int y = 0;
		while (std::getline(stream, line)) {
			std::vector<Vector2> iconsPos;
			lines.push_back(removeAllIcons(line, &iconsPos));
			if (icons)
			{
				for (auto i : iconsPos)
					icons->push_back({ (float)i.y,(float)y,(float)i.x });
			}
			y++;
		}
		return lines;
	}
	static float stepHeight = 1.0f;
	void DrawText(const char* text, float x, float y, float size, Color color,Vector2 rotationPoint,float angle)
	{
		//DrawTextPro(diffFont, text, { (float)x,(float)y }, rotationPoint, angle, size, 0.0f, color);
		//return;
		std::vector<Vector3> iconsToDraw;
		std::vector<std::string> splitedLines = splitLines(text, &iconsToDraw);
		Vector2 charPos = { x,y };
		for (auto s : splitedLines)
		{
			DrawTextPro(diffFont, s.c_str(), charPos, rotationPoint, angle, size, 0.0f, color);
			charPos.y += size * stepHeight;
		}
		const float bolder = 0.2f;
		for (auto icon : iconsToDraw)
		{
			int inTextx = icon.x;
			int inTexty = icon.y;
			int ID = icon.z;
			if (ID < 0 || ID >= icons.size())
				continue;
			std::string text = splitedLines[inTexty];
			std::string textToMesure = text.substr(0, inTextx);
			Vector2 textS = TextSize(textToMesure.c_str(), size, 0.0f);
			Rectangle pos = { x + textS.x + bolder * size,y + bolder * size,(1.0f - bolder * 2) * size,(1.0f - bolder * 2) * size };
			icons[ID].draw(pos);
		}
	}
	Vector2 TextSize(const char* text, float size, float spacing)
	{
		std::vector<std::string> splitedLines = splitLines(text);
		return { MeasureTextEx(diffFont, text, size, spacing).x,size * stepHeight * splitedLines.size() };
	}

	void DrawTextWithOutline(const char* text, float x, float y, float fontSize, Color textColor, Color outlineColor, Vector2 rotationPoint, float angle) {
		outlineColor.a = (outlineColor.a / 3);
		for (int ox = -OutlineSpacing; ox <= OutlineSpacing; ox += OutlineSpacing) {
			for (int oy = -OutlineSpacing; oy <= OutlineSpacing; oy += OutlineSpacing) {
				MyFont::DrawText(text, x + ox, y + oy, fontSize, outlineColor, rotationPoint, angle);
			}
		}
		MyFont::DrawText(text, x, y, fontSize, textColor, rotationPoint, angle);
	}

	float getFontSize()
	{
		return 64.0f;
	}
}