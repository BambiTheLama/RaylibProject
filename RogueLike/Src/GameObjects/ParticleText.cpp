#include "ParticleText.h"
#include "Game.h"

ParticleText::ParticleText(float x, float y, std::string text,Color color)
{
	this->color = color;
	this->text = text.c_str();
	int textSize = MeasureText(text.c_str(), 32);
	pos = { x - textSize / 2.0f,y - 32.0f,0,0 };
	lifeTime = lifeTimeMax;
	drawOrder = 10;
}

void ParticleText::update(float deltaTime)
{
	pos.y -= deltaTime * 10;
	lifeTime -= deltaTime;
	if (lifeTime <= 0)
		Game::deleteObject(this);
}

void ParticleText::draw()
{
	Color c = color;
	c.a = 255 * lifeTime / lifeTimeMax;
	MyFont::DrawTextWithOutline(text.c_str(), pos.x, pos.y, MyFont::getFontSize(), c, {0,0,0,c.a});
}