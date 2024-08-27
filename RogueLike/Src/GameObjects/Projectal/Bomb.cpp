#include "Bomb.h"
#include "../Game.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Characters/Wall.h"

Bomb::Bomb(float x, float y)
{
	
	pos = { x,y,64,64 };
	pos.x -= pos.width / 2;
	pos.y -= pos.height / 2;
	mass = 5;

	addCollisionElement(new CollisionElementLines({ pos.width / 4,pos.height / 4,pos.width/2,pos.height/2 }));
	time = timerMax;
}

void Bomb::start()
{
	texture = TextureController("Projectal/Bomb.png");
}

void Bomb::update(float deltaTime)
{
	time -= deltaTime;
	if (time <= 0.0f)
	{
		explode();
		Game::deleteObject(this);
	}
}

void Bomb::explode()
{
	Rectangle explodePos = pos;
	explodePos.x -= range;
	explodePos.width += 2 * range;
	float delta = tileW/2;
	while (explodePos.width > 0)
	{
		std::list<GameObject*> objs = Game::getObjects(explodePos);
		for (auto o : objs)
		{
			Hitable* hit = dynamic_cast<Hitable*>(o);
			if (hit)
				hit->dealDamage(damage);
			Wall* wall = dynamic_cast<Wall*>(o);
			if (wall)
				wall->deletePartWall(explodePos);
		}
		explodePos.x += delta;
		explodePos.width -= 2 * delta;
		explodePos.y -= delta;
		explodePos.height += 2 * delta;


	}
}

void Bomb::draw()
{
	int frame = (timerMax - time) / timerMax * texture.getFrames();
	texture.draw(pos, false, false, frame);
	//DrawFrameRec(pos, mixColor(YELLOW, RED, time / timerMax));
}