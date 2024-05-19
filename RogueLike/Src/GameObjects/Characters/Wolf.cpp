#include "Wolf.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "raymath.h"

Wolf::Wolf(int x, int y)
{
	pos = { (float)x,(float)y,64,32 };
	collisionElemnets.push_back(new CollisionElementBox({ pos.width / 4, pos.height / 4, pos.width / 2, pos.height / 2 }));
	type = ObjectType::Enemy;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = (int)Action::GoTo;
	controller.setController(ai);
	controller.setCharacter(this);
	
}

void Wolf::update(float deltaTime)
{
	Hitable::update(deltaTime);
	controller.update(deltaTime);
	if (ai && ai->target)
	{
		ai->action = 0;
		Rectangle pos = getPos();
		Rectangle otherPos = ai->target->getPos();
		Vector2 posV = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 otherPosV = { otherPos.x + otherPos.width / 2,otherPos.y + otherPos.height / 2 };
		float distance = Vector2Length(posV - otherPosV);
		if (distance < 200)
			ai->action |= (int)Action::Attack;

		ai->action |= (int)Action::GoTo;
			
	}
}

void Wolf::draw()
{
	DrawRectangleRec(pos, LIGHTGRAY);
	Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });
}

void Wolf::move(Vector2 dir, float deltaTime)
{
	if (recoveryTime > 0)
	{
		recoveryTime -= deltaTime;
		pos.x += dir.x * deltaTime * 20;
		pos.y += dir.y * deltaTime * 20;
		return;
	}
	if (attackTime <= 0)
	{
		pos.x += dir.x * deltaTime * 100;
		pos.y += dir.y * deltaTime * 100;

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

void Wolf::action(Input input)
{
	if (input == Input::Attack1 && attackTime <= 0.0f)
	{
		Rectangle pos = ai->target->getPos();
		Rectangle pos2 = getPos(); 
		Vector2 dir = { pos.x + pos.width / 2 - pos2.x - pos2.width / 2,pos.y + pos.height / 2 - pos2.y - pos2.height / 2 };
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

}

void Wolf::onHit()
{

}