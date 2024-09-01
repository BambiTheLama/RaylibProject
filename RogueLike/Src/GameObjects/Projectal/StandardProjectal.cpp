#include "StandardProjectal.h"
#include "../Collider/CollisionElementCircle.h"
#include "../Collider/CollisionElementLines.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"
#include "../Particle/TextureDestroyParticleSystem.h"

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
	angle = (Vector2Angle({ 0.0000001f,0.0000001f }, dir) ) * RAD2DEG + rotationDiff;
	drawOrder = 10;
	trigger = true;
	range = stats.getRange();
	rangeMax = range;
	wasParticleSpawned = false;
}

void StandardProjectal::destroy()
{
	triggerNode(WeaponNodeActivation::OnEffectEnd, stats);
	if (Game::isGameScene() &&!wasParticleSpawned)
	{
		wasParticleSpawned = true;
		Rectangle pos = getPos();
		pos.x -= rotationPoint.x;
		pos.y -= rotationPoint.y;
		Game::addObject(new TextureDestroyParticleSystem(texture, 0, pos, 5, 5, 0.3f, 400));
	}
}

void StandardProjectal::update(float deltaTime)
{
	frameTimer += deltaTime;
	pos.x += dir.x * stats.getSpeed() * deltaTime;
	pos.y += dir.y * stats.getSpeed() * deltaTime;
	range -= stats.getSpeed() * deltaTime;
	timer -= deltaTime;
	if (range <= 0.0f)
		Game::deleteObject(this);

	//angle += deltaTime * 100.0f;
}

void StandardProjectal::draw()
{
	//DrawCircleV({ pos.x + pos.width / 2, pos.y + pos.height / 2 }, pos.height / 2, BLACK);

	int frame = texture.getFrame("", (int)(frameTimer / timePerFrame));
	Color c = WHITE;
	if (target & (int)ObjectType::Player)
		c = RED;
	texture.draw(pos, false, false, frame, rotationPoint, angle, c);
}



void StandardProjectal::onTriggerEnter(Collider* collider)
{
	GameObject* colObj = collider->getThisObj();
	if (!colObj)
		return;
	if (colObj == owner)
		return;
	if ((int)colObj->getType() & target)
	{
		Hitable* hit = dynamic_cast<Hitable*>(colObj);
		if (hit)
		{
			Vector2 colDir = collider->getCollisionDir(this);
			collider->addForce(colDir, stats.getKnockback(), 1);
			hit->dealDamage(stats.getDamage());
			if (!hit->isAlive())
				triggerNode(WeaponNodeActivation::OnKill, stats);
			if (pirce-- <= 0)
				Game::deleteObject(this);

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
			Game::deleteObject(this);
		getAngle();
	}

}

float StandardProjectal::getAngle()
{
	angle = (Vector2Angle({ 0.0000001f,0.0000001f }, dir)) * RAD2DEG + rotationDiff;
	return angle;
}

void StandardProjectal::updateStatsAfterSetStats()
{
	pirce = stats.getPirce();
	bounce = stats.getBounce();
	range = stats.getRange();
	timer = stats.getUseTime();
	
}

void StandardProjectal::readData(nlohmann::json data, std::string type)
{
	if (!data.contains(type))
		return;
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
	if (data[type].contains("ScaleSize"))
	{
		float scale = data[type]["ScaleSize"];
		scaleColliderElements(scale);
		rotationPoint = Vector2Scale(rotationPoint, scale);
		pos.width *= scale;
		pos.height *= scale;
	}	
	if (data[type].contains("RotationDiff"))
		rotationDiff = data[type]["RotationDiff"];


}
