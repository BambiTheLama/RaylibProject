#include "ProjectalFactory.h"
#include "StandardProjectal.h"
#include "Explosion.h"

Projectal* ProjectalFactory::getProjectal(int ID)
{
	if (ID < 0)
		return NULL;
	switch (ID)
	{
	case 1:
		return new StandardProjectal();
	case 2:
		return new Explosion();
	default:
		break;
	}
	return NULL;
}