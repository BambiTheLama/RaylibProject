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
	readFromWeaponData(weaponType, col, variant, variant);
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
	updateWeaponSize();


	WeaponStats wnStats;
	wnStats.range = 1000;
	wnStats.rangeMultiplier = 1;
	wnStats.bounce = 3;

	WeaponNode wn(wnStats, WeaponNodeActivation::OnUse, 1);
	WeaponNodeItem* wni = new WeaponNodeItem("Icons/AngleIcon.png");
	wni->setWeaponNode(wn);
	addSlot(0, wni);


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
	BeginShaderMode(shader.getShader());
	if (owner)
		texture.draw(pos, mirror, flipHorizontal, 0, rotationPoint, angle);
	else
		drawIcon(pos, true);
	EndShaderMode();
}

void Sword::drawIcon(Rectangle pos, bool onlyIcon)
{
	texture.draw(pos, false, !flipHorizontal, 0, { 0.0f,0.0f }, 0.0f);
	if (onlyIcon)
		return;
	Color c = { 128,128,128,200 };
	float procent = 0.0f;
	if (reloadTime > 0)
		procent = reloadTime / stats.reloadTime;
	else if (useTime > 0)
	{
		procent = (useTime + stats.useTime * std::max(numberOfUse - 1, 0)) / (stats.useTime * std::max(stats.countOfUse, 1));
		c.b = 255;
	}
	DrawRing({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, c);
	DrawRingLines({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, pos.height / 4, pos.height / 2, procent * 360 - 90, -90, 30, BLACK);
}

void Sword::drawDescription(Rectangle pos, float textSize)
{
	float bolder = getFrameBolder();
	drawWeaponNodeStats({ pos.x + pos.width + 3 * bolder,pos.y,0,0 }, textSize, true);
	DrawFrameRounded(pos, BLUE, BLACK);
	Rectangle iconPos = Weapon::getSlotPos(pos, 0);
	DrawFrameRec(iconPos, YELLOW);
	drawIcon(RectangleDecreasSize(iconPos, 8));

	drawWeaponDescription({ pos.x,Weapon::getSlotPos(pos, 0,1).y,pos.width,pos.height }, textSize);
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

void Sword::readFromWeaponData(std::string weaponType, std::vector<Vector2>& col, int weaponTier, int variant )
{
	if (!weaponData.contains(weaponType))
		return;
	Weapon::readFromWeaponData(weaponType, weaponTier, variant);

	pos.width = weaponData[weaponType]["Size"][0];
	pos.height = weaponData[weaponType]["Size"][1];
	if (weaponData[weaponType].contains("FlipHorizontal"))
		flipHorizontal = weaponData[weaponType]["FlipHorizontal"];
	if (weaponData[weaponType].contains("Col"))
	{
		for (int i = 0; i < weaponData[weaponType]["Col"].size(); i++)
		{
			int x = weaponData[weaponType]["Col"][i][0];
			int y = weaponData[weaponType]["Col"][i][1];
			if (flipHorizontal)
				y = pos.height - y;
			col.push_back({ (float)x,(float)y });
		}
	}
}