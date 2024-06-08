#include "Sword.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementBox.h"
#include "../Game.h"
Sword::Sword(GameObject* owner)
{
	this->owner = owner;
	pos = { 0,0,69,69 };
	collisionElemnets.push_back(new CollisionElementLines(std::vector<Vector2>{{0, 0}, { 0,pos.height }, { pos.width,0 } }));
	Collider::getThisObj();
	trigger = true;
}

void Sword::update(float deltaTime)
{

	if (owner)
	{
		Rectangle p = owner->getPos();
		pos.x = p.x + p.width / 2;
		pos.y = p.y + p.height / 2;
	}
	if (IsKeyDown(KEY_Q))
		angle -= deltaTime * 72;
	if (IsKeyDown(KEY_E))
		angle += deltaTime * 72;
	{
		angle = angle - ((int)angle % 360) * 360;
	}
}

void Sword::draw()
{
	DrawRectanglePro(pos, { 0,0 }, angle, PINK);
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
	if (gm->getType() == ObjectType::Loot)
		Game::deleteObject(gm);

}