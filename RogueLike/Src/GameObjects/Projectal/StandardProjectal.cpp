#include "StandardProjectal.h"
#include "../Collider/CollisionElementCircle.h"
#include "../Collider/CollisionElementLines.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"

StandardProjectal::StandardProjectal()
{
	pos = { 0,0,16,16 };
	addCollisionElement(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 2));
}

StandardProjectal::StandardProjectal(nlohmann::json data, std::string type)
{
	readData(data, type);
}


void StandardProjectal::start()
{
	triggerNode(WeaponNodeActivation::OnUse, stats);
	angle = Vector2Angle({ 0.0000001f,0.0000001f }, dir) * RAD2DEG;
	drawOrder = 10;
	trigger = true;
}

void StandardProjectal::destroy()
{
	triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
}

void StandardProjectal::update(float deltaTime)
{
	pos.x += dir.x * stats.speed * deltaTime;
	pos.y += dir.y * stats.speed * deltaTime;
	range -= stats.speed * deltaTime;
	timer -= deltaTime;
	if (range <= 0.0f)
		Game::deleteObject(this);

}

void StandardProjectal::draw()
{
	//DrawCircleV({ pos.x + pos.width / 2, pos.y + pos.height / 2 }, pos.height / 2, BLACK);
	texture.draw(pos, false, false, 0, rotationPoint, angle);
}



void StandardProjectal::onTriggerEnter(Collider* collider)
{
	GameObject* colObj = collider->getThisObj();
	if (!colObj)
		return;
	if (colObj == owner)
		return;
	if ((int)colObj->getType() & (int)ObjectType::Enemy)
	{
		Hitable* hit = dynamic_cast<Hitable*>(colObj);
		if (hit)
		{
			hit->dealDamage(stats.damage);
			if (!hit->isAlive())
				triggerNode(WeaponNodeActivation::OnKill, stats);
			pirce--;
			if (pirce <= 0)
			{
				Game::deleteObject(this);
			}

			triggerNode(WeaponNodeActivation::OnHit, stats);
		}

	}
	else if ((int)colObj->getType() & (int)ObjectType::Wall)
	{
		Vector2 collisonDir = getCollisionDir(collider);
		if (abs(collisonDir.x) > abs(collisonDir.y))
			dir.x = -dir.x;
		else
			dir.y = -dir.y;
		if (bounce-- <= 0)
		{
			triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
			Game::deleteObject(this);
		}
	}
	else
	{
		Hitable* hit = dynamic_cast<Hitable*>(collider);
		if (hit)
		{
			hit->dealDamage(1.0f);
		}
	}
}


void StandardProjectal::updateStatsAfterSetStats()
{
	pirce = stats.pirce;
	bounce = stats.bounce;
	range = stats.range;
	timer = stats.useTime;
	
}

void StandardProjectal::readData(nlohmann::json data, std::string type)
{
	if (!data.contains(type))
		return;
	printf(data.dump(2).c_str());
	if (data[type].contains("Texture"))
		texture = TextureController(data[type]["Texture"]);
	if (data[type].contains("Size"))
	{
		pos.width = data[type]["Size"][0];
		pos.height = data[type]["Size"][1];
	}
	if (data[type].contains("RotationPoint"))
	{
		rotationPoint.x = data[type]["RotationPoint"][0];
		rotationPoint.y = data[type]["RotationPoint"][1];
	}

	if (data[type].contains("Col"))
	{
		std::vector<Vector2> lines;	
		for (int i = 0; i < data[type]["Col"].size(); i++)
		{
			float x = data[type]["Col"][i][0];
			float y = data[type]["Col"][i][1];
			lines.push_back({ x,y });
		}

		addCollisionElement(new CollisionElementLines(lines));
	}
	else
	{
		float range = fminf(pos.width / 2.0f, pos.height / 2.0f);

		addCollisionElement(new CollisionElementCircle({ pos.width / 2.0f,pos.height / 2.0f }, range));
	}

}
