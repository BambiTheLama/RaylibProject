#include "Font.h"
#include <sstream>
#include "Core/Controller/TextureController.h"
#include "raymath.hpp"
#include "Core/Controller/ShaderController.h"

static ShaderController outline;

namespace MyFont
{

	static Font diffFont;
	static std::vector<TextureController> icons;

	void SetUpFont()
	{
		outline = ShaderController("OutLine.frag");
		diffFont = LoadFontEx("Res/RobotoSlab-Regular.ttf", 512, 0, 255 * 2);
		SetTextureFilter(diffFont.texture, TEXTURE_FILTER_BILINEAR);
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
	void DrawText(const char* text, float x, float y, float size, Color color,Vector2 rotationPoint,float angle,bool withIcons)
	{
		std::vector<Vector3> iconsToDraw;
		std::vector<std::string> splitedLines = splitLines(text, &iconsToDraw);
		int i = 0;
		for (auto s : splitedLines)
		{
			DrawTextPro(diffFont, s.c_str(), { x,y }, { rotationPoint.x,rotationPoint.y - size * i }, angle, size, 0.0f, color);
			i++;
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
			std::string text = splitedLines[inTexty].substr(0, inTextx);
			Vector2 textS = TextSize(text.c_str(), size, 0.0f);
			Rectangle pos = { x ,y,(1.0f - bolder * 2) * size,(1.0f - bolder * 2) * size };
			Vector2 orgin = { rotationPoint.x - (textS.x + bolder * size),rotationPoint.y - size * (inTexty + bolder) };
			icons[ID].draw(pos, false, false, 0, orgin, angle, color);
		}
	}
	Vector2 TextSize(const char* text, float size, float spacing)
	{
		std::vector<std::string> splitedLines = splitLines(text);
		Vector2 textSize = { 0.0f ,size * splitedLines.size() };
		for (auto t : splitedLines)
		{
			float sizeX=MeasureTextEx(diffFont, t.c_str(), size, spacing).x;
			if (sizeX > textSize.x)
				textSize.x = sizeX;
		}
		return textSize;
	}

	void DrawTextWithOutline(const char* text, float x, float y, float fontSize, Color textColor, Color outlineColor, Vector2 rotationPoint, float angle) {
		const float size = 2;
		MyFont::DrawText(text, x - size, y, fontSize, outlineColor, rotationPoint, angle);
		MyFont::DrawText(text, x + size, y, fontSize, outlineColor, rotationPoint, angle);
		MyFont::DrawText(text, x, y - size, fontSize, outlineColor, rotationPoint, angle);
		MyFont::DrawText(text, x, y + size, fontSize, outlineColor, rotationPoint, angle);
		MyFont::DrawText(text, x, y, fontSize, textColor, rotationPoint, angle);

	}

	float getFontSize()
	{
		return 32.0f;
	}
}
#include "GameObjects/Game.h"

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
	return Game::convertFromWorldToScrean(rec);
}

void DrawSegmentLine(Vector2 start, Vector2 dir,float lineSize, float frame, float range, int segments, Color color)
{
	Rectangle rec=getRectangleFromVectors(start,dir,range);
	BeginScissorMode((int)(rec.x - lineSize / 2), (int)(rec.y - lineSize / 2), (int)(rec.width + lineSize), (int)(rec.height + lineSize));
	Vector2 dirDiff = { (dir.x * range) / (2 * segments),(dir.y * range) / (2 * segments) };
	Vector2 sv = Vector2Subtract(start, { dirDiff.x * 3,dirDiff.y * 3 });
	frame -= (int)frame;
	sv.x += 2 * frame * dirDiff.x;
	sv.y += 2 * frame * dirDiff.y;
	Vector2 ev = Vector2Add(sv, dirDiff);
	for (int i = 0; i < segments+2; i++)
	{
		DrawLineEx(sv, ev, lineSize, color);
		sv = Vector2Add(ev, dirDiff);
		ev = Vector2Add(sv, dirDiff);
	}
	//DrawCircleV(Vector2Add(start, { dir.x * range,dir.y * range }), 10, RED);
	EndScissorMode();
}

const float border = 20.0f;
void DrawFrameRounded(Rectangle pos, Color frameColor, Color outlineColor)
{
	const float randnes = 0.2f;
	const int segments = 1;
	const float lineSize = 3.0f;
	pos = RectangleIncreasSize(pos, border);
	DrawRectangleRounded(pos, randnes, segments, frameColor);
	DrawRectangleRoundedLines(RectangleDecreasSize(pos, lineSize), randnes, segments, lineSize, outlineColor);
}
void DrawFrameRec(Rectangle pos, Color frameColor, Color outlineColor)
{
	const float randnes = 0.5f;
	const int segments = 1;
	const float lineSize = 3.0f;
	DrawRectangleRounded(pos, randnes, segments, frameColor);
	DrawRectangleRoundedLines(RectangleDecreasSize(pos, lineSize - 1), randnes, segments, lineSize, outlineColor);
}


float getFrameBolder()
{
	return border;
}

Rectangle RectangleIncreasSize(Rectangle rec, float v)
{
	return { rec.x - v,rec.y - v,rec.width + v * 2,rec.height + v * 2 };
}

Rectangle RectangleDecreasSize(Rectangle rec, float v)
{
	return { rec.x + v,rec.y + v,rec.width - v * 2,rec.height - v * 2 };
}

float RectangleDistance(Rectangle r1, Rectangle r2)
{
	return Vector2Distance({ r1.x + r1.width / 2,r1.y + r1.height / 2 }, { r2.x + r2.width / 2,r2.y + r2.height / 2 });
}

void startOutLineShader()
{
	BeginShaderMode(outline.getShader());
}

Rectangle moveRectangeBy(Rectangle pos, Vector2 moveBy)
{
	return { pos.x + moveBy.x,pos.y + moveBy.y,pos.width,pos.height };
}

Vector2 getMidlePoint(Rectangle rec)
{
	return { rec.x + rec.width / 2,rec.y + rec.height / 2 };
}

Vector2 randVector2()
{
	return Vector2Normalize({ (rand() % 201) / 100.0f - 1.0f,(rand() % 201) / 100.0f - 1.0f });
}

Color mixColor(Color c1, Color c2, float p)
{
	p = Clamp(p, 0.0f, 1.0f);
	float p2 = 1.0f - p;
	return { (unsigned char)(c1.r * p + c2.r * p2),(unsigned char)(c1.g * p + c2.g * p2), (unsigned char)(c1.b * p + c2.b * p2), (unsigned char)(c1.a * p + c2.a * p2) };
}

Vector2 DirFromAngle(float angle)
{
	angle *= DEG2RAD;
	return { cosf(angle) - sinf(angle),sinf(angle) + cosf(angle) };
}
