#include "ParticleText.h"
#include "../Game.h"

int ParticleText::seed = 1000;

ParticleText::ParticleText(float x, float y, float time, std::string text,Color color)
{
	this->color = color;
	this->text = text;
	Vector2 size = MyFont::TextSize(text.c_str(), MyFont::getFontSize(), 0);
	pos = { x - size.x / 2 ,y,size.x,size.y };
	lifeTimeMax = time;
	lifeTime = lifeTimeMax;
	drawOrder = 10;
	angleRotation = getRandom(seed, -1.0f, 1.0f);
}

void ParticleText::update(float deltaTime)
{
	float procent = powf((lifeTime*4) / lifeTimeMax, 4.0f);
	angle = angleRotation * (1.0f - lifeTime) / lifeTimeMax * 90;
	pos.y -= deltaTime * procent * 2;
	lifeTime -= deltaTime;
	if (lifeTime <= 0)
		Game::deleteObject(this);
}

void ParticleText::draw()
{
	Color c = color;
	float procent = powf((lifeTime * 2) / lifeTimeMax, 6.0f);
	if (procent > 1.0f)
		procent = 1.0f;
	else if (procent < 0.0f)
		procent = 0.0f;

	c.a = (unsigned char)(255 * procent);
	MyFont::DrawTextWithOutline(text.c_str(), pos.x, pos.y, MyFont::getFontSize(), c, { 0,0,0,c.a }, { pos.width / 2,pos.height / 2 }, angle);

}