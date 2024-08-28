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
	Texture2D text = texture.getTexture();
	Color c = WHITE;
	if (timer > 0.0f)
		c.a *= timer / startTime;
	else
		c.a = 0;
	DrawTexturePro(text, textPos, pos, rotationPoint, angle, c);
}

TextureDestroyParticleSystem::TextureDestroyParticleSystem(TextureController texture,int frame, Rectangle pos, int w, int h, float timer, float speed)
{
	GameObject::pos = pos;
	this->texture = texture;
	this->timer = timer;
	if (w < 1)
		w = 1;
	if (h < 1)
		h = 1;
	const Texture2D text = texture.getTexture();
	const Vector2 frameSize = texture.getFrameSize();
	float startTexturePos = texture.getFrame("", frame) * frameSize.x;
	const float posW = pos.width / w;
	const float posH = pos.height / h;
	const float textureX = frameSize.x / w;
	const float textureY = frameSize.y / h;
	const int minAngle = -30.0f;
	const int maxAngle = 30.0f;
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			TextureDestroyParticle particle;
			particle.pos = { pos.x + posW * x,pos.y + posH * y,posW,posH };
			particle.textPos = { startTexturePos + textureX * x,textureY * y,textureX,textureY };
			particle.dir = DirFromAngle(GetRandomValue(0, 360));
			particle.rotationPoint = { posW / 2,posH / 2 };
			particle.anglePerSec = (float)GetRandomValue(minAngle, maxAngle);
			particle.timer = ((rand() % 1000) / 1000.0f) * timer / 2.0f + timer / 2.0f;
			particle.startTime = particle.timer;
			particle.speed = (rand() % 100) / 100.0f * speed / 2.0f + speed / 2.0f;

			particles.push_back(particle);
		}
	}


}

void TextureDestroyParticleSystem::setRotationPoint(Vector2 rotationPoint, float angle)
{
	for (auto& p : particles)
	{
		p.rotationPoint.x = pos.x - p.pos.x;
		p.rotationPoint.y = pos.y - p.pos.y;
		p.angle = angle;
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
	for (auto p : particles)
		p.draw(texture);
}
