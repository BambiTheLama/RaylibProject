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
	inputDir = { 0,0 };
	inputs.clear();
	findPathTimer -= deltaTime;

	if (action == 0)
	{
		return;
	}

	if (action == (int)Action::IDE)
	{
		if (abs(lastMoveDir.x) < 0.1 && abs(lastMoveDir.y) < 0.1)
		{
			lastMoveDir = { (rand() % 21) / 10.0f - 1.0f,(rand() % 21) / 10.0f - 1.0f };
		}
		else
		{
			Vector2 moveDiff = { (rand() % 2001) / 1000.0f - 1.0f,(rand() % 2001) / 1000.0f - 1.0f };
		
			lastMoveDir = Vector2Add(lastMoveDir, { moveDiff.x * deltaTime*10,moveDiff.y * deltaTime*10 });
		}
		moveDir = Vector2Normalize(lastMoveDir);
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
	{
		if (findPathTimer <= 0)
		{

			Rectangle posRec = target->getPos();
			Rectangle thisPosRec = thisObj->getPos();
			Vector2 runDir = Vector2Normalize(Vector2Subtract(getMidlePoint(target->getPos()), getMidlePoint(thisObj->getPos())));
			posRec.x = thisPosRec.x - runDir.x * range / 2.0f;
			posRec.y = thisPosRec.y - runDir.y * range / 2.0f;
			toGoDir = Game::getPathToGo(thisPosRec, posRec, (float)range);
			newToGoDir();

			findPathTimer = refresTimer;
		}
		toGoDirNow.z -= deltaTime * thisObj->getSpeed();
		lastMoveDir = Vector2Normalize({ toGoDirNow.x, toGoDirNow.y });
		if (toGoDirNow.z <= 0.0f)
		{
			newToGoDir();
		}
		moveDir = lastMoveDir;
	}

	if ((action & (int)Action::GoTo) != 0)
	{
		if (findPathTimer <= 0)
		{
			toGoDir = Game::getPathToGo(thisObj->getPos(), target->getPos(), range * 1.5f);
			newToGoDir();
			findPathTimer = refresTimer;
		}
		toGoDirNow.z -= deltaTime * thisObj->getSpeed();
		lastMoveDir = Vector2Normalize({ toGoDirNow.x, toGoDirNow.y });
		if (toGoDirNow.z <= 0.0f)
		{
			newToGoDir();
		}
		moveDir = lastMoveDir;
	}




	if ((action & (int)Action::Attack) != 0)
	{
		inputDir = Vector2Normalize(Vector2Subtract(getMidlePoint(target->getPos()), getMidlePoint(thisObj->getPos())));
		inputs.push_back(Input::Attack);
	}

}

void AIController::lookForTarget() {
	target = nullptr;
	Rectangle pos = RectangleIncreasSize(thisObj->getPos(), range);
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

void AIController::newToGoDir()
{
	if (toGoDir.size() > 0)
	{
		toGoDirNow = toGoDir.front();
		toGoDir.pop_front();
	}
	else
		toGoDirNow = { 0,0,0 };
}