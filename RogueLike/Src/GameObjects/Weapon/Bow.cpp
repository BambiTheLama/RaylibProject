#include "Bow.h"
#include "../Game.h"
#include "raymath.h"

Bow::Bow(std::string weaponType, int variant, nlohmann::json data, int weaponTier)
{
	type = ObjectType::Item;
	pos = { 0,0,32,32 };
	readFromWeaponData(weaponType, variant);
	if (data.contains(weaponType) && data[weaponType].size() > variant && variant >= 0)
		readStats(data[weaponType][variant], weaponTier);

	moving = true;
	setIsSpawn(true);

}

void Bow::start()
{
	Weapon::start();
	Item::start();
}

void Bow::use(Vector2 dir, float deltaTime)
{
	angle = Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / PI;
	loadTime += deltaTime;
	if (loadTime > stats.getUseTime())
		loadTime = stats.getUseTime();
}

void Bow::stopUse(Vector2 dir, float deltaTime)
{
	loadTime += deltaTime;
	if (loadTime >= stats.getUseTime())
	{
		triggerNode(WeaponNodeActivation::OnUse, stats);
		triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
	}

	loadTime = 0.0f;

}

void Bow::update(float deltaTime)
{
	if (owner)
	{
		Vector2 p = getMidlePoint(owner->getPos());
		pos.x = p.x;
		pos.y = p.y;
		Game::addObject(this);
	}
}

void Bow::update(float deltaTime, Vector2 dir)
{
	Item::update(deltaTime, dir);
	angle = Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / PI;
}

void Bow::draw(Rectangle pos)
{
	Vector2 rotationPoint = this->rotationPoint;
	float angle = this->angle;
	int frame = (int)(loadTime / stats.getUseTime() * (texture.getFrames() - 1));
	texture.draw(pos, false, false, frame, rotationPoint, angle + angleDiff);
}

void Bow::drawIcon(Rectangle pos, bool onlyIcon, Color color)
{
	texture.draw(pos, false, false, 0, { 0.0f,0.0f }, 0.0f, color);
	if (onlyIcon)
		return;
	Color c = { 128,128,128,200 };
	float procent = 0.0f;
	if (loadTime > 0)
	{
		procent = (loadTime) / (stats.getUseTime());
		c.b = 255;
	}
	DrawRing({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, c);
	DrawRingLines({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, BLACK);
}

void Bow::draw()
{
	Rectangle pos = getPos();
	if (isClosestObject)
	{
		startOutLineShader();
		const int lineSize = 4;
		draw(moveRectangeBy(pos, { 0,lineSize }));
		draw(moveRectangeBy(pos, { 0,-lineSize }));
		draw(moveRectangeBy(pos, { lineSize ,0 }));
		draw(moveRectangeBy(pos, { -lineSize,0 }));
		EndShaderMode();
	}
	draw(pos);
	drawWeaponPoints();
}

void Bow::readFromWeaponData(std::string weaponType, int variant)
{
	if (!weaponData.contains(weaponType))
		return;
	Weapon::readFromWeaponData(weaponType, variant);
	if (weaponData[weaponType].contains("Size"))
	{
		pos.width = weaponData[weaponType]["Size"][0];
		pos.height = weaponData[weaponType]["Size"][1];
	}
	if (weaponData[weaponType].contains("AngleDiff"))
		angleDiff = weaponData[weaponType]["AngleDiff"];
	if (weaponData[weaponType].contains("Scale"))
	{
		float scale = weaponData[weaponType]["Scale"];
		scaleWeapon(scale);
		pos.width *= scale;
		pos.height *= scale;
	}

}
