#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
#include "raymath.h"
#include "../AddisionalTypes/Hitable.h"
#include <fstream>
#include <math.h>

Sword::Sword(GameObject* owner, std::string weaponType, int variant)
{
	this->owner = owner;
	pos = { 0,0,32,32 };
	const char* cstrWeapon = weaponType.c_str();
	std::vector<Vector2> col;
	std::string texturePath = "Weapons/StoneSword.png";
	if (weaponData.contains(cstrWeapon))
	{

		pos.width = weaponData[cstrWeapon]["Size"][0];
		pos.height = weaponData[cstrWeapon]["Size"][1];
		if (weaponData[cstrWeapon].contains("Col"))
		{
			for (int i = 0; i < weaponData[cstrWeapon]["Col"].size(); i++)
			{
				int x = weaponData[cstrWeapon]["Col"][i][0];
				int y = weaponData[cstrWeapon]["Col"][i][1];
				col.push_back({ (float)x,(float)y });
			}
		}
		if (weaponData[cstrWeapon].contains("Textures"))
		{
			int numberOfTextures = weaponData[cstrWeapon]["Textures"].size();
			if (numberOfTextures > 0)
			{
				int textureId = variant % numberOfTextures;
				texturePath = weaponData[cstrWeapon]["Textures"][textureId];
			}
				

		}
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
	texture = TextureController(texturePath);

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
	Vector2 rotationPoint = this->rotationPoint;
	pos.x += rotationPoint.x;
	pos.y += rotationPoint.y;
	float angle = this->angle;

	if (mirror)
	{
		rotationPoint.x = pos.width - rotationPoint.x;
		angle -= 90;
	}
	texture.draw(pos, mirror, true, 0, rotationPoint, angle);
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

