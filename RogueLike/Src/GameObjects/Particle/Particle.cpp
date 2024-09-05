#include "Particle.h"
#include "raymath.h"
#include "../../Font.h"

void Particle::update(float deltaTime)
{
	size += deltaSize * deltaTime;
	speed += acceleration * deltaTime;
	timer -= deltaTime;
	angle += deltaTime * deltaAngle;
	pos = Vector2Add(pos, Vector2Scale(dir, speed * deltaTime));
}

Color Particle::getColor()
{
	if (colors.size() == 1)
		return colors[0];
	if (colors.size() > 1)
	{
		float procent = fabsf(timer / timerMax - 1.0f);
		int color = procent * colors.size();
		if (color + 1 >= colors.size() && color < colors.size())
		{
			return colors[color];
		}
		else
		{
			Color start = colors[color];
			Color end = colors[color + 1];
			return mixColor(start, end, color + 1 - procent * colors.size());
		}

	}
	return WHITE;
}

void Particle::draw(TextureController& texture, float scale)
{
	if (timer <= 0.0f)
		return;
	int frame = texture.getFrames() * timer / timerMax;
	Rectangle drawPos = { pos.x,pos.y,size * scale ,size * scale };
	Color color = getColor();
	texture.draw(drawPos, false, false, frame, { drawPos.width / 2,drawPos.height / 2 }, angle, color);
	//DrawCircleV(pos, size, getColor()); 
}