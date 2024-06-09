#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementBox.h"
#include "../Game.h"
#include "raymath.h"
#include "../AddisionalTypes/Hitable.h"

Sword::Sword(GameObject* owner)
{
	this->owner = owner;
	pos = { 0,0,69,69 };
	collisionElemnets.push_back(new CollisionElementLines(std::vector<Vector2>{{0, 0}, { pos.width*3.0f/8.0f,pos.height/2 }, { pos.width*13.0f/16.0f,pos.height }, { pos.width,pos.height }, { pos.width,pos.height * 13.0f / 16.0f }, { pos.width / 2.0f,pos.height * 3.0f / 8.0f } }));
	Collider::getThisObj();
	trigger = true;
	rotationPoint = { 0,0 };
	texture = LoadTexture("Res/Weapons/StoneSword.png");
}

void Sword::update(float deltaTime)
{
	if (owner)
	{
		Rectangle p = owner->getPos();
		pos.x = p.x + p.width / 2;
		pos.y = p.y + p.height / 2;
	}
	if (useTime > 0)
	{
		if (left)
			angle += deltaTime / useTimeMax * angleAttack;
		else
			angle -= deltaTime / useTimeMax * angleAttack;
		useTime -= deltaTime;
	}

}

void Sword::draw()
{
	Rectangle pos = getPos();
	pos.x += rotationPoint.x;
	pos.y += rotationPoint.y;
	//DrawRectanglePro(pos, rotationPoint, angle, PINK);
	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)-texture.height }, pos, rotationPoint, angle, WHITE);
	Collider::draw();
}

void Sword::use(Vector2 dir, float deltaTime)
{
	if (useTime <= 0)
	{
		left = !left;
		useTime = useTimeMax;
		angle = Vector2Angle({ 0.0000001f,0.0000001f }, dir) * 180 / 3.14159f;
		if (left)
			angle -= angleAttack / 2;
		else
			angle += angleAttack / 2;

	}
}

void Sword::onTriggerEnter(Collider* collider)
{
	if (!isUsing())
		return;
	GameObject* gm = collider->getThisObj();
	if (gm == owner || !gm)
		return;
	if (gm->getType() == ObjectType::Enemy)
	{
		Rectangle pos = gm->getPos();
		Vector2 vPos = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 rPos = Vector2Add(getRotationPoint(), getPosPoint());
		Hitable* hit = dynamic_cast<Hitable*>(collider);
		if (hit && hit->dealDamage(0))
			collider->addForce(Vector2Normalize(Vector2Subtract(vPos, rPos)), 800, 1);
	}


}