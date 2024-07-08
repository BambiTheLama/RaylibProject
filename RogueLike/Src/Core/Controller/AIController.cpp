#include "AIController.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/Game.h"
#include "raymath.h"

void AIController::update(float deltaTime)
{
	if (controllAction)
	{
		Controller::update(deltaTime);
		return;
	}
	moveDir = { 0,0 };
	inputs.clear();


	if ((action & (int)Action::IDE) != 0)
	{
		if (abs(IDEMoveDir.x) < 0.1 && abs(IDEMoveDir.x) < 0.1)
		{
			IDEMoveDir = { (rand() % 21) / 10.0f - 1.0f,(rand() % 21) / 10.0f - 1.0f };
		}
		else
		{
			Vector2 moveDiff = { (rand() % 2001) / 1000.0f - 1.0f,(rand() % 2001) / 1000.0f - 1.0f };
		
			IDEMoveDir = Vector2Add(IDEMoveDir, { moveDiff.x * deltaTime*10,moveDiff.y * deltaTime*10 });
		}
		IDEMoveDir = Vector2Normalize(IDEMoveDir);
		moveDir = IDEMoveDir;
	}
	else
	{
		IDEMoveDir = { 0,0 };
	}



	if (targerType == 0 || !thisObj)
		return;
	lookForTarget();
	if (!target)
	{
		return;
	}
	
	Vector2 pos = target->getPosPoint();
	Vector2 thisPos = thisObj->getPosPoint();
	if ((action & (int)Action::RunFrom) != 0)
		moveDir = Vector2Normalize(Vector2Subtract(thisPos, pos));
	if ((action & (int)Action::GoTo) != 0)
		moveDir = Vector2Normalize(Vector2Subtract(pos , thisPos));



	if ((action & (int)Action::Attack) != 0)
		inputs.push_back(Input::Attack1);
}

void AIController::lookForTarget() {
	target = nullptr;
	Rectangle pos = thisObj->getPos();
	pos.x -= range;
	pos.y -= range;
	pos.width += range * 2;
	pos.height += range * 2;
	std::list<GameObject*> objcts = Game::getObjects(pos);
	objcts.remove(thisObj);
	float dist = range * 2.0f;
	for (auto o : objcts)
	{
		if (((int)o->getType() & targerType) != 0)
		{
			Rectangle otherPos = o->getPos();
			float d = Vector2Distance({ pos.x + pos.width / 2,pos.y + pos.height / 2 }, 
				{ otherPos.x + otherPos.width / 2,otherPos.y + otherPos.height / 2 });
			if (!target ||dist>d)
			{
				target = o;
				dist = d;
			}
		}

	}
}