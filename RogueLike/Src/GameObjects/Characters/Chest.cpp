#include "Chest.h"
#include "../Collider/CollisionElementLines.h"

extern const float tileW;
extern const float tileH;

Chest::Chest(Rectangle pos, int tier)
{
	pos.width = tileW;
	pos.height = tileH;
	this->pos = pos;
	addCollisionElement(new CollisionElementLines({ 0,0,pos.width,pos.height }));
}
