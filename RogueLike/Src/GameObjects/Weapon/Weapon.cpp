#include "Weapon.h"
#include "../GameObject.h"
#include <fstream>

nlohmann::json Weapon::weaponData;

Weapon::Weapon()
{

}

void Weapon::update() 
{ 
	if (thisObj)
		thisObj->update(0.0f);
	else
		findThisObject();
}

bool Weapon::triggerNode(WeaponNodeActivation activation, WeaponStats stats)
{
	if (!thisObj)
		findThisObject();
	if (!thisObj)
		return false;
	printf("U¿yto %d\n", (int)activation);
	return weaponNodeTrigger.activateTrigger(activation, thisObj, stats);
	return false;
}

void Weapon::findThisObject()
{
	thisObj = dynamic_cast<GameObject*>(this);
}

void Weapon::loadWeaponData(std::string weaponDataPath)
{
	std::ifstream reader;
	reader.open(weaponDataPath);
	if (reader.is_open())
	{
		reader >> weaponData;
		reader.close();
	}
}