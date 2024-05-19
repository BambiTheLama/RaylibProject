#include "ParticleText.h"
#include "Game.h"

ParticleText::ParticleText(int x, int y, std::string text)
{

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
	Color c = RED;
	c.a = 255 * lifeTime / lifeTimeMax;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			DrawText(text.c_str(), pos.x-2+i, pos.y-2+j, 32, {0,0,0,c.a});
	DrawText(text.c_str(), pos.x, pos.y, 32, c);
}