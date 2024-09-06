#include "TextureDestroyParticleSystem.h"
#include "../Game.h"

void TextureDestroyParticle::update(float deltaTime)
{
	timer -= deltaTime;
	angle += anglePerSec * deltaTime;
	pos.x += dir.x * speed * deltaTime;
	pos.y += dir.y * speed * deltaTime;

}

void TextureDestroyParticle::draw(TextureController& texture)
{
	float scale = fmaxf(timer / startTime, 0.0f);
	Texture2D text = texture.getTexture();
	Rectangle pos = RectangleDecreasSize(this->pos, fminf(this->pos.width, this->pos.height) * (1.0f - scale) / 2);
	Color c = WHITE;
	c.a = (unsigned char)(c.a * scale);
	pos.x += pos.width / 2;
	pos.y += pos.height / 2;
	DrawTexturePro(text, textPos, pos, { pos.width / 2,pos.height / 2 }, angle, c);
}

int TextureDestroyParticleSystem::seed = 1000;

TextureDestroyParticleSystem::TextureDestroyParticleSystem(TextureController texture,int frame, Rectangle pos, int w, int h, float timer, float speed)
{
	drawOrder = 8;
	GameObject::pos = pos;
	this->texture = texture;
	this->timer = timer;
	if (w < 1)
		w = 1;
	if (h < 1)
		h = 1;
	const Texture2D text = texture.getTexture();
	const Vector2 frameSize = texture.getFrameSize();
	float startTexturePos = frame * frameSize.x;
	const float posW = pos.width / w;
	const float posH = pos.height / h;
	const float textureX = frameSize.x / w;
	const float textureY = frameSize.y / h;
	const int minAngle = -30;
	const int maxAngle = 30;
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			TextureDestroyParticle particle;
			particle.pos = { pos.x + posW * x,pos.y + posH * y,posW,posH };
			particle.textPos = { startTexturePos + textureX * x,textureY * y,textureX,textureY };
			particle.dir = DirFromAngle((float)getRandom(seed, 0, 360));
			particle.anglePerSec = (float)getRandom(seed, minAngle, maxAngle);
			particle.timer = getRandom(seed, (int)(timer * 100), (int)(timer * 1000)) / 1000.0f;
			particle.startTime = particle.timer;
			particle.speed = (float)getRandom(seed, (int)(speed / 2), (int)speed);

			particles.push_back(particle);
		}
	}


}

void TextureDestroyParticleSystem::update(float deltaTime)
{
	for (auto& p : particles)
		p.update(deltaTime);
	timer -= deltaTime;
	if (timer < 0.0f)
		Game::deleteObject(this);

}

void TextureDestroyParticleSystem::draw()
{
	//DrawRectangleRec(pos, RED);
	//DrawRectangleRec(pos, { 255,0,255,69 });
	for (auto p : particles)
		p.draw(texture);
}
