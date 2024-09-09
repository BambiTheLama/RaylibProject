#include "Coin.h"
#include "../Game.h"
#include "../Particle/ParticleText.h"
#include "../Collider/CollisionElementCircle.h"

extern const float tileW;
extern const float tileH;

Coin::Coin(Rectangle pos, int coins)
{
	const float w = tileW * 2;
	const float h = tileW * 2;
	pos = { (pos.width - w) / 2 + pos.x ,(pos.height - h) / 2 + pos.y,w,h };
	this->pos = pos;



	type = ObjectType::Coins;
	this->coins = coins;
	texture = TextureController("Elements/Coins.png");
	moving = false;
	trigger = true;
	addCollisionElement(new CollisionElementCircle({ pos.width/2,pos.height/2 }, pos.width / 5));
}

void Coin::start()
{
	particleAcctivated = false;
}

void Coin::destroy()
{
	if (!Game::isGameScene() || particleAcctivated)
		return;
	Vector2 pos = getMidlePoint(getPos());
	Game::addObject(new ParticleText(pos.x, pos.y, 1, "{Icon:11}"+ std::to_string(coins), ORANGE));
	particleAcctivated = true;
}

void Coin::update(float deltaTime)
{
}

void Coin::draw()
{
	texture.draw(pos);
}
