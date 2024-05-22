#include "Wolf.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "../AddisionalTypes/Collider/CollisionElementCircle.h"
#include "raymath.h"

Wolf::Wolf(int x, int y)
{
	pos = { (float)x,(float)y,64,32 };
	collisionElemnets.push_back(new CollisionElementBox({ pos.width / 4, pos.height / 4, pos.width / 2, pos.height / 2 }));
	//collisionElemnets.push_back(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 2));
	type = ObjectType::Enemy;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = (int)Action::GoTo;
	ai->range = 500;
	controller.setController(ai);
	controller.setCharacter(this);
	
}

void Wolf::update(float deltaTime)
{
	Hitable::update(deltaTime);
	controller.update(deltaTime);
	if (ai)
	{
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


		
	
	}
}

void Wolf::draw()
{
	DrawRectangleRec(pos, LIGHTGRAY);
	Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });
	if (!ai)
		return;
	return;
	float range = ai->range;
	Color c = { 0,0,0,25 };
	if ((ai->action & (int)Action::GoTo) != 0)
		c.g = 255;
	if ((ai->action & (int)Action::Attack) != 0)
		c.r = 255;
	DrawRectangle(pos.x - range, pos.y - range, pos.width + range * 2, pos.height + range * 2, c);
}

void Wolf::move(Vector2 dir, float deltaTime)
{
	if (recoveryTime > 0)
	{
		recoveryTime -= deltaTime;
		pos.x += dir.x * deltaTime * 20;
		pos.y += dir.y * deltaTime * 20;
		attackDir = dir;
		return;
	}
	if (attackTime <= 0)
	{
		pos.x += dir.x * deltaTime * 100;
		pos.y += dir.y * deltaTime * 100;
		attackDir = dir;

	}
	else
	{
		attackTime -= deltaTime;

		pos.x += attackDir.x * deltaTime * 200;
		pos.y += attackDir.y * deltaTime * 200;
		if (attackTime <= 0)
			recoveryTime = recoveryTimeMax;
	}
}

void Wolf::action(Input input, Vector2 dir)
{
	if (input == Input::Attack1 && attackTime <= 0.0f)
	{
		if (abs(dir.x) <= 0.1 && abs(dir.y) < 0.1)
			return;
		attackDir = Vector2Normalize(dir);
		


		attackTime = attackTimeMax;
	}

}

void Wolf::onCollisionEnter(Collider* collider)
{
	GameObject* gm = collider->getThisObj();
	if (((int)gm->getType() & target) != 0) {
		Hitable* hit = dynamic_cast<Hitable*>(gm);
		if (hit)
		{
			hit->dealDamage(damge);
		}
	}

}

void Wolf::destoryController()
{
	controller.destoryController();
	ai = nullptr;
}

void Wolf::onHit()
{

}