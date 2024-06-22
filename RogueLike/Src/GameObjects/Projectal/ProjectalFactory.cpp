#include "ProjectalFactory.h"
#include "StandardProjectal.h"

Projectal* ProjectalFactory::getProjectal(int ID)
{
	if (ID < 0)
		return NULL;
	switch (ID)
	{
	case 1:
		return new StandardProjectal();
	default:
		break;
	}
	return NULL;
}