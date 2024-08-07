#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
#include "raymath.h"
#include "../AddisionalTypes/Hitable.h"
#include <fstream>
#include <math.h>

#pragma region Constructor
Sword::Sword(std::string weaponType, int variant, nlohmann::json data,int weaponTier)
{
	type = ObjectType::Item;
	pos = { 0,0,32,32 };
	std::vector<Vector2> col;
	readFromWeaponData(weaponType, col, variant);
	if (data.contains(weaponType) && data[weaponType].size() > variant && variant >= 0)
		readStats(data[weaponType][variant], weaponTier);
	Collider::difSize = { pos.width,pos.height };
	addCollisionElement(new CollisionElementLines(col));
	Collider::getThisObj();
	moving = true;
	mass = 1;
	updateWeaponSize();
	//setIsSpawn(true);
	//setSpawnID(1);
}

Sword::~Sword()
{
}
#pragma endregion Constructor

void Sword::start()
{
	Weapon::start();
	Item::start();
}

void Sword::update(float deltaTime)
{
	if (owner)
	{
		Vector2 p = getMidlePoint(owner->getPos());
		pos.x = p.x;
		pos.y = p.y;
		Game::addObject(this);
	}
	if (reloadTime > 0)
	{
		reloadTime -= deltaTime;
		return;
	}
	if (useTime > 0)
	{
		if (left)
			angle += deltaTime / useTimeMax * stats.angle;
		else
			angle -= deltaTime / useTimeMax * stats.angle;
		if (!used && useTime < useTimeMax / 2)
		{
			triggerNode(WeaponNodeActivation::OnUse, stats);
			used = true;
		}
		useTime -= deltaTime;
		if (useTime <= 0.0f)
		{
			numberOfUse--;

			if (numberOfUse <= 0)
			{
				reloadTime = stats.reloadTime;
				numberOfUse = stats.countOfUse;
			}
			else
			{

				useTime = useTimeMax;
				used = false;
				left = !left;
			}
			Collider::mirror = left;
			Weapon::mirror = left;
		}
	}
}

void Sword::use(Vector2 dir, float deltaTime)
{
	if (useTime <= 0 && reloadTime <= 0)
	{
		numberOfUse = stats.countOfUse;
		left = !left;
		useTimeMax = stats.useTime / std::max(stats.countOfUse, 1);
		useTime = useTimeMax;
		angle = Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / PI;
		if (left)
			angle -= stats.angle / 2;
		else
			angle += stats.angle / 2;
		Collider::mirror = left;
		Weapon::mirror = left;
		used = false;
		updateWeaponSize();
	}
}

void Sword::onTriggerEnter(Collider* collider)
{
	if (!isUsing())
		return;
	GameObject* gm = collider->getThisObj();
	if (gm == owner || !gm)
		return;
	if ((int)gm->getType() & (int)ObjectType::Enemy)
	{
		Rectangle pos = gm->getPos();
		Vector2 vPos = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 rPos = Vector2Add(getRotationPoint(), getPosPoint());
		Hitable* hit = dynamic_cast<Hitable*>(collider);
		if (hit && hit->dealDamage(stats.damage))
		{
			if (!hit->isAlive())
				triggerNode(WeaponNodeActivation::OnKill, stats);
			collider->addForce(Vector2Normalize(Vector2Subtract(vPos, rPos)), stats.knockback * stats.knockbackMultiplier, 1);
			triggerNode(WeaponNodeActivation::OnHit, stats);
		}
		return;
	}
	Hitable* hit = dynamic_cast<Hitable*>(collider);
	if (hit)
	{
		hit->dealDamage(1.0f);
	}

}

#pragma region DrawFun
void Sword::draw(Rectangle pos)
{
	Vector2 rotationPoint = this->rotationPoint;
	float angle = this->angle;

	if (Collider::mirror)
	{
		rotationPoint.x = pos.width - rotationPoint.x;
		angle -= 90;
	}

	texture.draw(pos, Collider::mirror, flipHorizontal, 0, rotationPoint, angle);
}

void Sword::draw()
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

void Sword::drawIcon(Rectangle pos, bool onlyIcon, Color color)
{
	texture.draw(pos, false, !flipHorizontal, 0, { 0.0f,0.0f }, 0.0f, color);
	if (onlyIcon)
		return;
	Color c = { 128,128,128,200 };
	float procent = 0.0f;
	if (reloadTime > 0)
		procent = reloadTime / stats.reloadTime;
	else if (useTime > 0)
	{
		procent = (useTime + (numberOfUse - 1) * (useTimeMax)) / (stats.useTime);
		c.b = 255;
	}
	DrawRing({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, c);
	DrawRingLines({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, BLACK);
}
#pragma endregion DrawFun

#pragma region Setters

void Sword::setOwner(GameObject* owner)
{
	Item::setOwner(owner);
	
	if (!owner)
	{
		angle = 0.0f;
	}
	trigger = owner;
	flipHorizontal = owner;
	flipHorizontalElements(flipHorizontal);
}

#pragma endregion Setters

#pragma region Getters

Vector2 Sword::getRotationPoint() 
{ 
	return rotationPoint;
}

#pragma endregion Getters


void Sword::updateWeaponSize()
{
	float scale = (stats.range) / pos.width;
	pos.width *= scale;
	pos.height *= scale;
	rotationPoint.x *= scale;
	rotationPoint.y *= scale;
	scaleColliderElements(scale);

}

void Sword::readFromWeaponData(std::string weaponType, std::vector<Vector2>& col, int variant)
{
	if (!weaponData.contains(weaponType))
		return;
	Weapon::readFromWeaponData(weaponType, variant);
	if (weaponData[weaponType].contains("Size"))
	{
		pos.width = weaponData[weaponType]["Size"][0];
		pos.height = weaponData[weaponType]["Size"][1];
	}
	if (weaponData[weaponType].contains("FlipHorizontal"))
		flipHorizontal = weaponData[weaponType]["FlipHorizontal"];
	if (weaponData[weaponType].contains("Col"))
	{
		for (int i = 0; i < weaponData[weaponType]["Col"].size(); i++)
		{
			int x = weaponData[weaponType]["Col"][i][0];
			int y = weaponData[weaponType]["Col"][i][1];
			col.push_back({ (float)x,(float)y });
		}
	}
}