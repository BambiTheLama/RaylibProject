#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Game.h"
#include "raymath.h"
#include "../AddisionalTypes/Hitable.h"
#include <fstream>
#include <math.h>
#include <rlgl.h>

#pragma region Constructor
Sword::Sword(std::string weaponType, int variant, nlohmann::json data,int weaponTier)
{
	type = ObjectType::Item;
	pos = { 0,0,32,32 };
	readFromWeaponData(weaponType, variant);
	int variantToRead = 0;
	if (data.contains(weaponType))
	{
		if (!data[weaponType].is_array())
			readStats(data[weaponType], weaponTier);
		else
		{
			variantToRead = (int)Clamp((float)variant, 0, data[weaponType].size() - 1.0f);
			if (data[weaponType].size() > variantToRead)
				readStats(data[weaponType][variantToRead], weaponTier);
		}

	}

	Collider::difSize = { pos.width,pos.height };
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
	numberOfUseMax = stats.getCountOfUse();
	numberOfUse = numberOfUseMax;
}

void Sword::update(float deltaTime)
{
	updateWeaponSize();
	if (reloadTime > 0)
	{
		reloadTime -= deltaTime;
		points.clear();
		return;
	}
	else if (useTime > 0)
	{

		if (left)
			angle += deltaTime / useTimeMax * rotationAgnel;
		else
			angle -= deltaTime / useTimeMax * rotationAgnel;
		if (!used && useTime < useTimeMax / 2)
		{
			triggerNode(WeaponNodeActivation::OnUse, stats);
			used = true;
		}
		useTime -= deltaTime;

		addLineTimer -= deltaTime;
		if (addLineTimer <= 0 || fabs(lastAngle - angle) > angleDiffMax)
		{
			Vector2 p = DirFromAngle(angle);
			Vector2 p2 = Vector2Multiply(p, rotationPoint);
			float size = (pos.width + pos.height) / 3;
			float offset = size / 8;
			float dif = abs((useTime / useTimeMax) * 2 - 1) * size / 2;
			points.push_back(Vector2Add({ pos.x - p2.x,pos.y - p2.y }, Vector2Scale(p, offset + dif)));
			points.push_back(Vector2Add({ pos.x - p2.x,pos.y - p2.y }, Vector2Scale(p, offset + size - dif)));
			addLineTimer = addLineTimerMax;
			lastAngle = angle;
		}


		if (useTime <= 0.0f)
		{
			triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
			numberOfUse--;
			points.clear();
			if (numberOfUse <= 0)
			{
				reloadTime  = stats.getReloadTime();
				numberOfUse = stats.getCountOfUse();
			}
			else
			{
				used = false;
				angle = getWeaponRotation();
			}
			addLineTimer = 0.0f;


		}
	}
}

void Sword::update(float deltaTime, Vector2 dir)
{
	Item::update(deltaTime, dir);
	faceingDir = dir;
	if (useTime <= 0 && reloadTime <= 0)
		angle = getWeaponRotation();

}

void Sword::use(Vector2 dir, float deltaTime)
{
	if (useTime <= 0 && reloadTime <= 0 && numberOfUse >= 0)
	{
		if (!hasOwnRotationAngle)
			rotationAgnel = Clamp(stats.getAngle(), 0.0f, 360);
		if (!hasDefineNumberOfUse)
		{
			numberOfUseMax = stats.getCountOfUse();
			if (numberOfUse <= 0)
				numberOfUse = numberOfUseMax;
		}

		//numberOfUse = numberOfUseMax;
		left = !left;
		useTimeMax = stats.getUseTime();
		useTime = useTimeMax;

		Collider::mirror = left != flipHorizontal;
		Weapon::mirror = left != flipHorizontal;
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
	if ((int)gm->getType() & target)
	{
		Vector2 colDir = collider->getCollisionDir(this);
		Hitable* hit = dynamic_cast<Hitable*>(collider);
		if (hit && hit->dealDamage(stats.getDamage()))
		{
			if (!hit->isAlive())
				triggerNode(WeaponNodeActivation::OnKill, stats);
			collider->addForce(colDir, stats.getKnockback(), 1);
			triggerNode(WeaponNodeActivation::OnHit, stats);
		}
	}

}

#pragma region DrawFun
void Sword::draw(Rectangle pos, Color c)
{
	Vector2 rotationPoint = this->rotationPoint;
	float angle = this->angle;

	bool mirror = Collider::mirror;

	if (mirror)
	{
		rotationPoint.x = pos.width - rotationPoint.x;
		angle -= 90;
	}

	texture.draw(pos, mirror, flipHorizontal, 0, rotationPoint, angle, c);


}

void Sword::draw()
{
	Rectangle pos = getPos();
	if (isClosestObject)
	{
		startOutLineShader();
		const int lineSize = 4;
		draw(moveRectangeBy(pos, { 0,lineSize }), WHITE);
		draw(moveRectangeBy(pos, { 0,-lineSize }),WHITE);
		draw(moveRectangeBy(pos, { lineSize ,0 }),WHITE);
		draw(moveRectangeBy(pos, { -lineSize,0 }),WHITE);
		EndShaderMode();
	}
	if (points.size() > 0)
	{
		rlEnableBackfaceCulling();
		unsigned char colorA = (unsigned char)(200 * (-powf(2 * useTime / useTimeMax - 1, 2)+10));
		DrawTriangleStrip(points.data(), (int)points.size(), GetColor(0xaab6cc00 + colorA));
		rlDisableBackfaceCulling();
	}

	draw(pos, WHITE);
	//drawWeaponPoints();
}

void Sword::drawIcon(Rectangle pos, bool onlyIcon, Color color)
{
	texture.draw(pos, false, !flipHorizontal, 0, { 0.0f,0.0f }, 0.0f, color);
	if (onlyIcon)
		return;
	Color c = { 128,128,128,200 };
	float procent = 0.0f;
	if (reloadTime > 0)
		procent = reloadTime / stats.getReloadTime();
	else if (useTime > 0)
	{
		procent = useTime / useTimeMax;
		procent = (useTime + (numberOfUse - 1) * (useTimeMax)) / (std::max(numberOfUseMax, 1) * useTimeMax);
		c.b = 255;
	}
	else
	{
		procent = (float)numberOfUse / std::max(numberOfUseMax, 1);
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
	flipHorizontal = (bool)(owner) == flipHorizontalFromFile;
	flipHorizontalElements(flipHorizontal);
}

#pragma endregion Setters

#pragma region Getters

Vector2 Sword::getRotationPoint() 
{ 
	float scale = 1.0f;
	if (useTime > 0.0f)
	{
		if (numberOfUse <= 1)
			scale = fabsf((useTime / useTimeMax));
		else
			scale = fabsf((useTime / useTimeMax) - 0.5f) * 2;

	}
	else if (reloadTime > 0.0f)
	{
		scale = fabsf((reloadTime / stats.getReloadTime()) - 1.0f);
	}
	rotationPoint = Vector2Add(Vector2Scale(rotationPointStart, scale), Vector2Scale(rotationPointEnd, 1.0f - scale));
	return rotationPoint;
}

#pragma endregion Getters


void Sword::updateWeaponSize()
{
	if (!isRangeScale)
		return;
	float scale = (stats.getRange() * rangeScale);
	if (scale == lastScaleRange)
		return;

	scaleWeapon(scale);


}

void Sword::scaleWeapon(float scale)
{

	if (scale <= 0 || lastScaleRange == scale)
		return;
	float s = scale/lastScaleRange;
	pos.width *= s;
	pos.height *= s;
	scaleColliderElements(s);
	Weapon::scaleWeapon(s);
	lastScaleRange = scale;
}

float Sword::getWeaponRotation()
{
	if (!hasOwnRotationAngle)
		rotationAgnel = Clamp(stats.getAngle(), 0.0f, 360);
	float angle = Vector2Angle({ 0.0000001f,0.0000001f }, faceingDir) * 180 / PI;
	if (!left)
		return angle - rotationAgnel / 2;
	return angle + rotationAgnel / 2;
}

void Sword::readFromWeaponData(std::string weaponType, int variant)
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
		flipHorizontalFromFile = weaponData[weaponType]["FlipHorizontal"];
	if (weaponData[weaponType].contains("FlipVertical"))
		flipVertical = weaponData[weaponType]["FlipVertical"];
	if (weaponData[weaponType].contains("Col"))
	{
		Collider::readColliders(weaponData[weaponType]["Col"]);
	}
	if (weaponData[weaponType].contains("RangeScale"))
	{
		rangeScale = weaponData[weaponType]["RangeScale"];
		isRangeScale = true;
	}
	if (weaponData[weaponType].contains("RotationAngle"))
	{
		rotationAgnel = weaponData[weaponType]["RotationAngle"];
		hasOwnRotationAngle = true;
	}
	if (weaponData[weaponType].contains("NumberOfUse"))
	{
		numberOfUseMax = weaponData[weaponType]["NumberOfUse"];
		hasDefineNumberOfUse = true;
	}
	if (weaponData[weaponType].contains("Scale"))
	{
		float scale = weaponData[weaponType]["Scale"];
		scaleWeapon(scale);
	}
}