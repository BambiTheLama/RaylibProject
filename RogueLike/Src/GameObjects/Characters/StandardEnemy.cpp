#include "StandardEnemy.h"
#include "../Collider/CollisionElementCircle.h"
#include "../Collider/CollisionElementLines.h"
#include "raymath.h"
#include "../Game.h"
#include "../ParticleText.h"

StandardEnemy::StandardEnemy(std::string type, nlohmann::json data, int level)
{

	pos = { 0,0,64.0f,64.0f };
	//addCollisionElement(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 4));
	//addCollisionElement(new CollisionElementLines({ pos.width / 3+4,pos.height / 3 + 10,pos.width / 3-8,pos.height / 3 }));
	this->type = ObjectType::Enemy;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = (int)Action::GoTo;
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
	
	ai->action = 0;
	Rectangle pos = getPos();
	if (target != 0 && ai->target)
	{
		Rectangle otherPos = ai->target->getPos();
		Vector2 posV = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 otherPosV = { otherPos.x + otherPos.width / 2,otherPos.y + otherPos.height / 2 };
		float distance = Vector2Length(Vector2Subtract(posV, otherPosV));
		if (distance < 200)
			ai->action |= (int)Action::Attack;
		
		ai->action |= (int)Action::GoTo;
	}
	else
	{
		ai->lookForTarget();
		ai->action |= (int)Action::IDE;
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
	Color c = { 0,0,0,25 };
	if ((ai->action & (int)Action::GoTo) != 0)
		c.g = 255;
	if ((ai->action & (int)Action::Attack) != 0)
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
			hit->dealDamage(damge, 0.2f);
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
}
