#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
#include "raymath.h"
#include "../AddisionalTypes/Hitable.h"
#include <fstream>
#include <math.h>

Sword::Sword(GameObject* owner, std::string weaponType, int variant)
{
	setOwner(owner);
	pos = { 0,0,32,32 };
	std::vector<Vector2> col;
	std::string texturePath = "Weapons/StoneSword.png";
	readFromWeaponData(weaponType, variant, col, texturePath);
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
	texture = TextureController(texturePath);

	updateWeaponSize();

	printf(stats.toString().c_str());

	setNumberOfSlots(2);
	
	WeaponStats wnStats;
	wnStats.range = 100;
	wnStats.rangeMultiplier = 1;
	wnStats.bounce = 3;

	WeaponNode wn(wnStats, WeaponNodeActivation::OnUse, 1);
	addSlot(0, &wn);
	wnStats.range = 0;
	wnStats.rangeMultiplier = 0.5;
	wnStats.angle = 360;
	wnStats.countOfUse = 1;
	WeaponNode wn2 = WeaponNode(wnStats, WeaponNodeActivation::OnEffectEnd, 2);
	addSlot(1, &wn2);
	wnStats.range = 100;
	wnStats.countOfUse = 20;
	WeaponNode wn3 = WeaponNode(wnStats, WeaponNodeActivation::OnEffectEnd, 1);
	addSlot(2, &wn3);
	wnStats.countOfUse = 1;
	WeaponNode wn4 = WeaponNode(wnStats, WeaponNodeActivation::OnEffectEnd, 2);
	addSlot(3, &wn4);
	
}

void Sword::update(float deltaTime)
{
	if (owner)
	{
		Rectangle p = owner->getPos();
		pos.x = p.x + p.width / 2;
		pos.y = p.y + p.height / 2;
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
			mirror = left;
		}
	}
}

void Sword::draw()
{
	Rectangle pos = getPos();	
	Vector2 rotationPoint = this->rotationPoint;
	//pos.x += rotationPoint.x;
	//pos.y += rotationPoint.y;
	float angle = this->angle;

	if (mirror)
	{
		rotationPoint.x = pos.width - rotationPoint.x;
		angle -= 90;
	}
	texture.draw(pos, mirror, true, 0, rotationPoint, angle);
}

void Sword::drawIcon(Rectangle pos)
{
	texture.draw(pos, false, false, 0, rotationPoint, 0.0f);
	Color c = { 128,128,128,200 };
	float procent = 0.0f;
	if (reloadTime > 0)
		procent = reloadTime / stats.reloadTime;
	else if (useTime > 0)
	{
		procent = (useTime + stats.useTime * (numberOfUse - 1)) / (stats.useTime * stats.countOfUse);
		c.b = 255;
	}
	DrawRing({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, c);
	DrawRingLines({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, BLACK);
	if (CheckCollisionPointRec(GetMousePosition(), pos))
	{
		drawDescription({ 800,500 }, 1000);
	}
}

void Sword::drawDescription(Vector2 center, float wight)
{
	const float textSize = 32;
	std::string desc = stats.toString();
	const char* cDesc = desc.c_str();
	Vector2 size = MyFont::TextSize(cDesc, textSize, 0);
	int x = center.x - wight / 2;
	int y = center.y - size.y;
	const float border = 20.0f;
	Rectangle rec = { x - border, y - border,wight + 2 * border, size.y + 2 * border };
	DrawRectangleRounded(rec, 0.2, 1, RED);
	DrawRectangle(x, y, wight, size.y, BLUE);
	MyFont::DrawTextWithOutline(cDesc, x, y, textSize, WHITE, BLACK);
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
	rotationPoint.x *= scale;
	rotationPoint.y *= scale;
	scaleColliderElements(scale);

}

void Sword::readFromWeaponData(std::string weaponType,int variant, std::vector<Vector2>& col, std::string &texturePath)
{
	if (!weaponData.contains(weaponType))
		return;
	
	pos.width = weaponData[weaponType]["Size"][0];
	pos.height = weaponData[weaponType]["Size"][1];
	if (weaponData[weaponType].contains("Col"))
	{
		for (int i = 0; i < weaponData[weaponType]["Col"].size(); i++)
		{
			int x = weaponData[weaponType]["Col"][i][0];
			int y = weaponData[weaponType]["Col"][i][1];
			col.push_back({ (float)x,(float)y });
		}
	}
	if (weaponData[weaponType].contains("Textures"))
	{
		int numberOfTextures = weaponData[weaponType]["Textures"].size();
		if (numberOfTextures > 0)
		{
			int textureId = variant % numberOfTextures;
			texturePath = weaponData[weaponType]["Textures"][textureId];
		}
	}
	if (weaponData[weaponType].contains("RotationPoint"))
	{
		rotationPoint.x = weaponData[weaponType]["RotationPoint"][0];
		rotationPoint.y = weaponData[weaponType]["RotationPoint"][1];
	}
	stats.readStatsFromWeapon(weaponData[weaponType], 0);
	
}