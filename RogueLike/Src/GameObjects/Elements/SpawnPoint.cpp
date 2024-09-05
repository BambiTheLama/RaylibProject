#include "SpawnPoint.h"
#include "../Game.h"

SpawnPoint::SpawnPoint(float x, float y, BlockType type)
{
	moving = false;
	this->type = type;
	pos = { x,y,tileW,tileH };
	GameObject::type = ObjectType::SpawnPoint;
	//drawOrder = 10;
	
}

void SpawnPoint::update(float deltaTime)
{
	return;
	std::list<GameObject*>objs = Game::getObjects(RectangleIncreasSize(pos, 500));
	for (auto o : objs)
	{
		if (o->getType() != ObjectType::Player)
			continue;
		Rectangle playerPos = o->getPos();
		o->setPos(getMidlePoint(pos));
		break;
	}
	Game::deleteObject(this);
}