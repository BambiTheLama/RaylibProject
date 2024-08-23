#include "StandardEnemy.h"
#include "../Collider/CollisionElementCircle.h"
#include "../Collider/CollisionElementLines.h"
#include "raymath.h"
#include "../Game.h"
#include "../ParticleText.h"
#include <magic_enum/magic_enum.hpp>

StandardEnemy::StandardEnemy(std::string type, nlohmann::json data, int level)
{

	pos = { 0,0,64.0f,64.0f };
	//addCollisionElement(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 4));
	//addCollisionElement(new CollisionElementLines({ pos.width / 3+4,pos.height / 3 + 10,pos.width / 3-8,pos.height / 3 }));
	this->type = ObjectType::Enemy;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = Action::GoTo;
	ai->range = 300;
	controller.setController(ai);
	controller.setCharacter(this);
	controller.setCharacterType(ObjectType::Enemy);
	mass = 10;
	//trigger = true;
	texture = TextureController("Enemies/Skeletron.png");
	readData(type, data, level);
}

void StandardEnemy::destroy()
{

}

void StandardEnemy::update(float deltaTime)
{
	frameTimer += deltaTime;
	Hitable::update(deltaTime);
	controller.update(deltaTime);
	if (!ai)
		return;

	Rectangle pos = getPos();
	if (target != 0 && ai->target)
	{
		Vector2 posV = getMidlePoint(pos);
		Vector2 otherPosV = getMidlePoint(ai->target->getPos());
		float distance = Vector2Length(Vector2Subtract(posV, otherPosV));
		if (distance > maxRangeAttack)
			ai->setAction(Action::GoTo);
		else if (distance > minRangeAttack)
			ai->setAction(Action::Attack);
		else
			ai->setAction(Action::RunFrom);
	}
	else
	{
		ai->lookForTarget();
		ai->setAction(Action::IDE);
	}
	std::string actionName = ai->getActionName();
	if (actionName.compare(animationName))
	{
		frameTimer = 0.0f;
		animationName = actionName;
	}
}

void StandardEnemy::draw()
{
	//DrawRectangleRec(pos, col ?RED: LIGHTGRAY);
	int frame = texture.getFrame(animationName, frameTimer / timePerFrame);
	texture.draw(pos, false, false, frame);
	Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });
	DrawLineEx({ dir.x*75 + pos.x + pos.width / 2,dir.y*75 + pos.y + pos.height / 2 }, { pos.x + pos.width / 2,pos.y + pos.height / 2 }, 3, BLACK);
	if (!ai)
		return;

	float range = (float)ai->range;
	Color c = { 0,0,0,10 };
	if ((ai->action == Action::GoTo) != 0)
		c.g = 255;
	if ((ai->action == Action::Attack) != 0)
		c.r = 255;
	DrawRectangleRec({ pos.x - range, pos.y - range, pos.width + range * 2, pos.height + range * 2 }, c);
	
}

void StandardEnemy::action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime)
{
	return;
	if (input == Input::Attack && attackTime <= 0.0f)
	{
		if (abs(cursorDir.x) <= 0.1 && abs(cursorDir.y) < 0.1)
			return;
		attackDir = Vector2Normalize(cursorDir);

		attackTime = attackTimeMax;
	}

}

void StandardEnemy::onCollision(Collider* collider)
{
	GameObject* gm = collider->getThisObj();
	if (((int)gm->getType() & target) != 0) {
		Hitable* hit = dynamic_cast<Hitable*>(gm);
		if (hit)
		{
			hit->dealDamage(contactDamage, 0.2f);
		}
	}

}

void StandardEnemy::destoryController()
{
	controller.destoryController();
	ai = nullptr;
}

void StandardEnemy::onHit()
{

}

void StandardEnemy::readData(std::string type, nlohmann::json data, int level)
{
	if (!data.contains(type))
		return;
	if (data[type].contains("Size"))
	{
		pos.width = data[type]["Size"][0];
		pos.height = data[type]["Size"][1];
	}
	if (data[type].contains("Texture"))
		texture = TextureController(data[type]["Texture"]);

	if (data[type].contains("Col"))
	{
		std::vector<Vector2> col;
		
		for (int i = 0; i < data[type]["Col"].size(); i++)
		{
			int x = data[type]["Col"][i][0];
			int y = data[type]["Col"][i][1];
			col.push_back({ (float)x,(float)y });
		}
		addCollisionElement(new CollisionElementLines(col));
	}
	if (data[type].contains("Mass"))
		mass = data[type]["Mass"];
	if (data[type].contains("Range"))
		ai->range = data[type]["Range"];
	if (data[type].contains("Scale"))
	{
		float scale = data[type]["Scale"];

		Collider::scaleColliderElements(scale);
		pos.width *= scale;
		pos.height *= scale;
	}
	if (data[type].contains("Spawn"))
	{
		spawn = true;
		std::string spawnName = data[type]["Spawn"];
		auto castData = magic_enum::enum_cast<ProjectalID>(spawnName);
		if (castData.has_value())
			spawnID = castData.value();

	}
	if (data[type].contains("MinDist"))
		minRangeAttack = data[type]["MinDist"];
	if (data[type].contains("MaxDist"))
		maxRangeAttack = data[type]["MaxDist"];
	if (data[type].contains("AttackCDR"))
		attackCDR = data[type]["AttackCDR"];
	if (data[type].contains("ContactDamage"))
		contactDamage = data[type]["ContactDamage"];

	ws.readStatsFromWeapon(data[type]);
	
}
