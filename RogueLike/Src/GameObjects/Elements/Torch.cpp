#include "Torch.h"
#include "../Game.h"
#include "../Collider/CollisionElementLines.h"

Torch::Torch(Rectangle pos)
{
	this->pos = pos;
	texture = TextureController("Elements/Torch.png");
	addCollisionElement(new CollisionElementLines({ pos.width / 3,pos.height / 2,pos.width / 3,pos.height / 2 }));
	solidObject = true;
	moving = false;
	type = ObjectType::Loot;
	//mass = 100;
}

void Torch::start()
{
	LightObject::setRange(300);
	LightObject::colorCenter = {255,169,56,255};
	LightObject::colorEnd = { 255,56,169,255 };
}

void Torch::update(float deltaTime)
{
	LightObject::update(deltaTime);
	Hitable::update(deltaTime);
	frameTimer += deltaTime;
}

void Torch::draw()
{
	int frame = texture.getFrames() * (frameTimer / timePerFrame / 5);
	texture.draw(pos, false, false, frame);
}

void Torch::onHit()
{
	Game::deleteObject(this);
}
