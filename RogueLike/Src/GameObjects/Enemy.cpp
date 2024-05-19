#include "Enemy.h"
#include "../Core/AIController.h"
#include "raymath.h"
#include "AddisionalTypes/Collider/CollisionElementBox.h"

Enemy::Enemy(int x, int y)
{
	pos = { (float)x, (float)y, 48, 64 };
	pos.x -= pos.width / 2;
	pos.y -= pos.height / 2;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = (int)Action::GoTo;
	controller.setController(ai);
	controller.setCharacter(this);
	type = ObjectType::Enemy;
	collisionElemnets.push_back(new CollisionElementBox({ pos.width / 4, pos.height / 4, pos.width / 2, pos.height / 2 }));
}

void Enemy::update(float deltaTime)
{
	controller.update(deltaTime);
	if (ai->target)
	{
		Rectangle pos = getPos();
		Rectangle otherPos = ai->target->getPos();
		Vector2 posV = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 otherPosV = { otherPos.x + otherPos.width / 2,otherPos.y + otherPos.height / 2 };
		float distance = Vector2Length(posV - otherPosV);
		if (distance < 100)
			ai->action = (int)Action::Run;
		else if (distance > 200)
			ai->action = (int)Action::GoTo;
	}
}

void Enemy::draw()
{
	DrawRectangleRec(pos, PINK);
}

void Enemy::move(Vector2 dir, float deltaTime)
{
	pos.x += dir.x * deltaTime * 100;
	pos.y += dir.y * deltaTime * 100;
}

void Enemy::action(Input input)
{

}

void Enemy::onCollisionEnter(Collider* col)
{
	GameObject* gm = col->getThisObj();
	if (gm && ((int)gm->getType() & ai->targerType) > 0)
	{
		ai->target = gm;
	}

}