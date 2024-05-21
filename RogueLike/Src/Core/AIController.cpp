#include "AIController.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Game.h"
#include "raymath.h"

void AIController::update(float deltaTime)
{
	moveDir = { 0,0 };
	inputs.clear();
	if (targerType == 0 || !thisObj)
		return;
	lookForTarget();
	if (!target)
	{
		return;
	}
	Vector2 pos = target->getPosPoint();
	Vector2 thisPos = thisObj->getPosPoint();
	if ((action & (int)Action::Run) != 0)
		moveDir = Vector2Normalize(Vector2Subtract(thisPos, pos));
	if ((action & (int)Action::GoTo) != 0)
		moveDir = Vector2Normalize(Vector2Subtract(pos , thisPos));

	if ((action & (int)Action::Attack) != 0)
		inputs.push_back(Input::Attack1);
}

void AIController::lookForTarget() {
	Rectangle pos = thisObj->getPos();
	pos.x -= range;
	pos.y -= range;
	pos.width += range * 2;
	pos.height += range * 2;
	std::list<GameObject*> objcts = Game::getObjects(pos);
	objcts.remove(thisObj);
	for (auto o : objcts)
	{
		if (((int)o->getType() & targerType) != 0)
		{
			target = o;
			return;
		}

	}
}