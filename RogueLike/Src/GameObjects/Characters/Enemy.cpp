#include "Enemy.h"
#include "../../Core/AIController.h"
#include "raymath.h"
#include "../Collider/CollisionElementLines.h"

Enemy::Enemy(float x, float y)
{
	hp = 100;
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
	std::vector<Vector2> col{
		{pos.width / 4,					pos.height / 4},
		{pos.width / 4 + pos.width / 2,	pos.height / 4},
		{pos.width / 4 + pos.width / 2,	pos.height / 4 + pos.height / 2},
		{pos.width / 4,					pos.height / 4 + pos.height / 2}
	};
	collisionElemnets.push_back(new CollisionElementLines(col));
}

void Enemy::update(float deltaTime)
{
	Hitable::update(deltaTime);
	controller.update(deltaTime);
	if (ai && ai->target)
	{
		Rectangle pos = getPos();
		Rectangle otherPos = ai->target->getPos();
		Vector2 posV = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 otherPosV = { otherPos.x + otherPos.width / 2,otherPos.y + otherPos.height / 2 };
		float distance = Vector2Length(Vector2Subtract(posV , otherPosV));
		if (distance < 100)
			ai->action = (int)Action::RunFrom;
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
	pos.x += dir.x * deltaTime * speed;
	pos.y += dir.y * deltaTime * speed;
}

void Enemy::action(Input input)
{

}

void Enemy::onCollisionEnter(Collider* col)
{
	GameObject* gm = col->getThisObj();
	if (gm && ai && ((int)gm->getType() & ai->targerType) > 0)
	{
		ai->target = gm;
	}


}

void Enemy::destoryController()
{
	controller.destoryController();
	ai = nullptr;
}

void Enemy::onHit()
{
	speed+=5;
}