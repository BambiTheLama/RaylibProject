#include "ProjectalFactory.h"
#include "StandardProjectal.h"
#include "Explosion.h"
#include "magic_enum/magic_enum.hpp"

Projectal* getProjectal(std::string projectalName, Vector2 dir)
{
	
	auto enumCast = magic_enum::enum_cast<ProjectalID>(projectalName);
	if (enumCast.has_value())
		return getProjectal(enumCast.value(), dir);
	return nullptr;
}

Projectal* getProjectal(ProjectalID projectalID,Vector2 dir)
{
	switch (projectalID)
	{
	case ProjectalID::Arrow:
	case ProjectalID::Shuriken:
	case ProjectalID::Bomb:
		return new StandardProjectal();
		break;
	default:
		break;
	}
	return NULL;
}