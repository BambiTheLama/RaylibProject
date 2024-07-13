#include "Font.h"
#include <sstream>
#include "Core/Controller/TextureController.h"
#include "raymath.hpp"

namespace MyFont
{

	static Font diffFont;
	static std::vector<TextureController> icons;

	void SetUpFont()
	{
		diffFont = LoadFontEx("Res/PatrickHand.ttf",256,0,255*2);
		//diffFont = LoadFont("Res/PatrickHand.ttf");
		icons.push_back(TextureController("Icons/DamageIcon.png"));
		icons.push_back(TextureController("Icons/UseTimeIcon.png"));
		icons.push_back(TextureController("Icons/ReloadIcon.png"));
		icons.push_back(TextureController("Icons/SpeedIcon.png"));
		icons.push_back(TextureController("Icons/RangeIcon.png"));
		icons.push_back(TextureController("Icons/AngleIcon.png"));
		icons.push_back(TextureController("Icons/KnockbackIcon.png"));
		icons.push_back(TextureController("Icons/CountOfUseIcon.png"));
		icons.push_back(TextureController("Icons/BounceIcon.png"));
		icons.push_back(TextureController("Icons/PirceIcon.png"));
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
				for (int i = (int)find; i < text.size(); i++)
				{
					if (text[i] == '}')
					{
						toErase = i - (int)find + 1;
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
	void DrawText(const char* text, float x, float y, float size, Color color,Vector2 rotationPoint,float angle,bool withIcons)
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
		if (!withIcons)
			return;
		const float bolder = 0.2f;
		for (auto icon : iconsToDraw)
		{
			int inTextx = (int)icon.x;
			int inTexty = (int)icon.y;
			int ID = (int)icon.z;
			if (ID < 0 || ID >= icons.size())
				continue;
			std::string text = splitedLines[inTexty];
			std::string textToMesure = text.substr(0, inTextx);
			Vector2 textS = TextSize(textToMesure.c_str(), size, 0.0f);
			Rectangle pos = { x + textS.x + bolder * size,y + size * (stepHeight * inTexty + bolder),(1.0f - bolder * 2) * size,(1.0f - bolder * 2) * size };
			icons[ID].draw(pos, false, false, 0, { 0.0f,0.0f }, 0.0f, color);
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

Rectangle getRectangleFromVectors(Vector2 start, Vector2 dir,float range)
{
	Rectangle rec;
	rec.x = start.x;
	rec.y = start.y;
	rec.width = dir.x * range;
	rec.height = dir.y * range;
	if (rec.width < 0)
	{
		rec.x += rec.width;
		rec.width = -rec.width;
	}
	if (rec.height < 0)
	{
		rec.y += rec.height;
		rec.height = -rec.height;
	}
	return rec;
}

void DrawSegmentLine(Vector2 start, Vector2 dir,float lineSize, float frame, float range, int segments, Color color)
{
	Rectangle rec=getRectangleFromVectors(start,dir,range);
	BeginScissorMode(rec.x, rec.y, rec.width, rec.height);
	Vector2 dirDiff = { (dir.x * range) / (2 * segments),(dir.y * range) / (2 * segments) };
	Vector2 sv = Vector2Subtract(start, { dirDiff.x * 3,dirDiff.y * 3 });
	sv.x += frame * dirDiff.x/segments;
	sv.y += frame * dirDiff.y/segments;
	Vector2 ev = Vector2Add(sv, dirDiff);
	for (int i = 0; i < segments+2; i++)
	{
		DrawLineEx(sv, ev, lineSize, color);
		sv = Vector2Add(ev, dirDiff);
		ev = Vector2Add(sv, dirDiff);
	}
	DrawCircleV(Vector2Add(start, { dir.x * range,dir.y * range }), 10, RED);
	EndScissorMode();
}