#include "Torch.h"
#include "../Game.h"
#include "../Collider/CollisionElementLines.h"
#include "../Particle/TextureDestroyParticleSystem.h"

Torch::Torch(Rectangle pos)
{
	this->pos = pos;
	texture = TextureController("Elements/Torch.png");
	addCollisionElement(new CollisionElementLines({ pos.width / 3,pos.height / 2,pos.width / 3,pos.height / 2 }));
	solidObject = true;
	moving = false;
	type = ObjectType::Loot;
	particle = new FierParticle({ pos.x+15,pos.y+12 });
	//mass = 100;
}

Torch::~Torch()
{
	delete particle;
}



void Torch::start()
{
	LightObject::setRange(300);
	LightObject::colorCenter = {255,169,56,255};
	LightObject::colorEnd = { 255,56,169,255 };
	particleActivated = false;
	lightPosDiff = { pos.width / 2,pos.height / 2 };
}

void Torch::destroy()
{
	if (!Game::isGameScene())
		return;

	if (!particleActivated)
	{
		int frame = texture.getFrame("", (int)(frameTimer / timePerFrame));
		Game::addObject(new TextureDestroyParticleSystem(texture, 0, getPos()));
		particleActivated = true;
	}
}

void Torch::update(float deltaTime)
{
	LightObject::update(deltaTime);
	Hitable::update(deltaTime);
	frameTimer += deltaTime;
	particle->update(deltaTime);
}

void Torch::draw()
{
	int frame = (int)(texture.getFrames() * (frameTimer / timePerFrame / 5));
	texture.draw(pos, false, false, frame);
	particle->draw();
}

void Torch::drawLight()
{
	LightObject::drawLight();
	particle->draw();
}


void Torch::onHit()
{
	Game::deleteObject(this);
}
