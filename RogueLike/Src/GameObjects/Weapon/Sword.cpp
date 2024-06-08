#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementBox.h"
#include "../Game.h"
#include "raymath.h"
Sword::Sword(GameObject* owner)
{
	this->owner = owner;
	pos = { 0,0,69,69 };
	collisionElemnets.push_back(new CollisionElementLines(std::vector<Vector2>{{0, 0}, { 0,pos.height }, { pos.width,0 } }));
	Collider::getThisObj();
	trigger = true;
	rotationPoint = { 0,0 };
}

void Sword::update(float deltaTime)
{

	Vector2 mouse = GetMousePosition();
	mouse.x -= GetScreenWidth() / 2;
	mouse.y -= GetScreenHeight() / 2;
	mouse = Vector2Normalize(mouse);

	if (owner)
	{
		Rectangle p = owner->getPos();
		pos.x = p.x + p.width / 2;
		pos.y = p.y + p.height / 2;
	}
	angle = Vector2Angle({ 0.0000001f,0.0000001f }, mouse) * 180 / 3.14159f;
	printf("%lf\n", angle);

}

void Sword::draw()
{
	Rectangle pos = getPos();
	pos.x += rotationPoint.x;
	pos.y += rotationPoint.y;
	DrawRectanglePro(pos, rotationPoint, angle, PINK);
	Collider::draw();
}

void Sword::use(Vector2 dir, float deltaTime)
{

}

void Sword::onTriggerEnter(Collider* collider)
{
	GameObject* gm = collider->getThisObj();
	if (gm == owner || !gm)
		return;
	if (gm->getType() == ObjectType::Enemy)
	{
		Rectangle pos = gm->getPos();
		Vector2 vPos = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		Vector2 rPos = Vector2Add(getRotationPoint(), getPosPoint());

		collider->addForce(Vector2Normalize(Vector2Subtract(vPos, rPos)), 4, 2);
	}


}