#include "Wolf.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "../AddisionalTypes/Collider/CollisionElementCircle.h"
#include "raymath.h"
#include "../Game.h"
#include "../ParticleText.h"

Wolf::Wolf(float x, float y)
{
	pos = { x,y,64,32 };
	collisionElemnets.push_back(new CollisionElementBox({ pos.width / 4, pos.height / 4, pos.width / 2, pos.height / 2 }));
	//collisionElemnets.push_back(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 2));
	type = ObjectType::Enemy;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = (int)Action::GoTo;
	ai->range = 300;
	controller.setController(ai);
	controller.setCharacter(this);
	controller.setCharacterType(ObjectType::Enemy);
}

void Wolf::destroy()
{
	Game::addObject(new ParticleText(pos.x, pos.y, "KURWA UMIERAM"));
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
		else
		{
			ai->action |= (int)Action::IDE;
		}

	}
	else
	{
		move({ 0,0 }, deltaTime);
	}
}

void Wolf::draw()
{
	DrawRectangleRec(pos, LIGHTGRAY);
	Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });
	DrawLineEx({ dir.x*75 + pos.x + pos.width / 2,dir.y*75 + pos.y + pos.height / 2 }, { pos.x + pos.width / 2,pos.y + pos.height / 2 }, 3, BLACK);
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
	this->dir = dir;
	if (recoveryTime > 0)
	{
		speed = 20;
		recoveryTime -= deltaTime;
		pos.x += dir.x * deltaTime * speed;
		pos.y += dir.y * deltaTime * speed;
		attackDir = dir;
		return;
	}
	if (attackTime <= 0)
	{
		speed = 100;
		pos.x += dir.x * deltaTime * speed;
		pos.y += dir.y * deltaTime * speed;
		attackDir = dir;

	}
	else
	{
		attackDir = Vector2Normalize(Vector2Add({ dir.x * deltaTime * 2,dir.y * deltaTime * 2 }, attackDir));
		attackTime -= deltaTime;
		speed = 200;
		pos.x += attackDir.x * deltaTime * speed;
		pos.y += attackDir.y * deltaTime * speed;
		if (attackTime <= 0)
			recoveryTime = recoveryTimeMax;
		this->dir = attackDir;
	}
}

void Wolf::action(Input input, Vector2 dir,float deltaTime)
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