#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
#include "raymath.h"
#include "../AddisionalTypes/Hitable.h"
#include "json.hpp"
#include <fstream>
#include <math.h>
Sword::Sword(GameObject* owner)
{
	this->owner = owner;
	const char* colType = "Sword";
	pos = { 0,0,69,69 };
	std::ifstream reader;

	std::vector<Vector2> col;
	reader.open("Res/Weapon.json");
	if (reader.is_open())
	{
		nlohmann::json j;
		reader >> j;
		if (j.contains(colType))
		{

			pos.width = j[colType]["Size"][0];
			pos.height = j[colType]["Size"][1];
			if (j[colType].contains("Col"))
			{
				for (int i = 0; i < j[colType]["Col"].size(); i++)
				{
					int x = j[colType]["Col"][i][0];
					int y = j[colType]["Col"][i][1];
					col.push_back({ (float)x,(float)y });
				}
			}
		}
		reader.close();
	}
	if(col.size()<=0)
	{
		col = {
				{0, 0},
				{ pos.width,0 },
				{ pos.width,pos.height },
				{ 0,pos.height }
		};
	}

	collisionElemnets.push_back(new CollisionElementLines(col));
	Collider::getThisObj();
	trigger = true;

	rotationPoint = { 0,0 };
	texture = LoadTexture("Res/Weapons/StoneSword.png");
	WeaponNodeTrigger wnt;
	WeaponStats wnStats;
	wnStats.range = 100;
	wnStats.rangeMultiplier = 1;
	wnStats.bounce = 3;
	WeaponNode wn(wnStats, WeaponNodeActivation::OnUse, 1);
	wnt.pushBackNodeTrigger(wn);
	wnStats.range = 0;
	wnStats.rangeMultiplier = 0.5;
	wnStats.angle = 360;
	wnStats.countOfUse = 1;
	wn = WeaponNode(wnStats, WeaponNodeActivation::OnEffectEnd, 2);
	wnt.pushBackNodeTrigger(wn);
	wnStats.range = 100;
	wnStats.countOfUse = 20;
	wn = WeaponNode(wnStats, WeaponNodeActivation::OnEffectEnd, 1);
	wnt.pushBackNodeTrigger(wn);
	wnStats.countOfUse = 1;
	wn = WeaponNode(wnStats, WeaponNodeActivation::OnEffectEnd, 2);
	wnt.pushBackNodeTrigger(wn);
	setWeaponNodeTrigger(wnt);
	stats.angle = 180.0f;
	stats.countOfUse = 1;
	stats.useTime = 0.3f;
	stats.rangeMultiplier = 1.0f;
	stats.range = pos.width / stats.rangeMultiplier * 2.0f;
	updateWeaponSize();
}

void Sword::update(float deltaTime)
{
	if (owner)
	{
		Rectangle p = owner->getPos();
		pos.x = p.x + p.width / 2;
		pos.y = p.y + p.height / 2;
	}
	if (reloadTime > 0)
	{
		reloadTime -= deltaTime;
		return;
	}
	if (useTime > 0)
	{
		if (left)
			angle += deltaTime / stats.useTime * stats.angle;
		else
			angle -= deltaTime / stats.useTime * stats.angle;
		if (!used && useTime < stats.useTime / 2)
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
				useTime = stats.useTime;
				used = false;
				left = !left;
			}
		}
	}
}

void Sword::draw()
{
	Rectangle pos = getPos();
	pos.x += rotationPoint.x;
	pos.y += rotationPoint.y;
	Vector2 rotationPoint = this->rotationPoint;
	Rectangle textPos = { 0,0,(float)texture.width,(float)-texture.height };
	float angle = this->angle;
	if (mirror)
	{
		rotationPoint.x = pos.width - rotationPoint.x;
		textPos.width = -textPos.width;
		angle -= 90;
	}

	DrawTexturePro(texture, textPos, pos, rotationPoint, angle, WHITE);
	//Collider::draw();
}

void Sword::use(Vector2 dir, float deltaTime)
{
	if (useTime <= 0 && reloadTime <= 0)
	{
		numberOfUse = stats.countOfUse;
		left = !left;
		useTime = stats.useTime;
		angle = Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / PI;
		if (left)
			angle -= stats.angle / 2;
		else
			angle += stats.angle / 2;
		mirror = left;
		used = false;
		updateWeaponSize();
	}
}
Vector2 Sword::getRotationPoint() 
{ 
	return rotationPoint;
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

	}


}
void Sword::updateWeaponSize()
{
	float scale = (stats.range * stats.rangeMultiplier) / pos.width;
	pos.width *= scale;
	pos.height *= scale;
	scaleColliderElements(scale);
}

