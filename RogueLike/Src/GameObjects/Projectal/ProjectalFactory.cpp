#include "ProjectalFactory.h"
#include "StandardProjectal.h"
#include "Explosion.h"
#include "magic_enum/magic_enum.hpp"

static nlohmann::json projectalData;

void setUpProjectals(std::string path)
{
	projectalData = readJson(path+"Projectal.json");
}

Projectal* getProjectal(std::string projectalName, Vector2 dir)
{
	
	auto enumCast = magic_enum::enum_cast<ProjectalID>(projectalName);
	if (enumCast.has_value())
		return getProjectal(enumCast.value(), dir);
	return nullptr;
}

Projectal* getProjectal(ProjectalID projectalID,Vector2 dir)
{
	auto toString = magic_enum::enum_name(projectalID);
	const char* text = toString.data();
	switch (projectalID)
	{
	case ProjectalID::Arrow:
	case ProjectalID::Shuriken:
	case ProjectalID::Bomb:
		return new StandardProjectal(projectalData, text);
		break;
	default:
		break;
	}
	return NULL;
}