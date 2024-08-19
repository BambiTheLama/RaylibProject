#pragma once
#include "Projectal.h"

void setUpProjectals(std::string path);

Projectal* getProjectal(std::string projectalName, Vector2 dir = { 0,0 });

Projectal* getProjectal(ProjectalID projectalID, Vector2 dir = { 0,0 });


