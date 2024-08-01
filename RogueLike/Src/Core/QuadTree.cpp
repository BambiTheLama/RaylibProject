#include "QuadTree.h"
#include <algorithm>
#include "raymath.h"

QuadTree::QuadTree(Rectangle pos)
{
	this->pos = pos;
}

void QuadTree::addObj(GameObject* o)
{
	if (roots[0])
	{
		for (int i = 0; i < 4; i++)
			if (CheckCollisionRecs(o->getPos(), roots[i]->pos))
				roots[i]->addObj(o);
	}
	auto find = std::find(objects.begin(), objects.end(), o);
	if (find != objects.end())
	{
		return;
	}

	objects.push_back(o);
	if (!roots[0] && objects.size() >= 10)
		openTree();

}

void QuadTree::update()
{
	if (!roots[0])
		return;

	for (auto o : objects)
	{
		for (int i = 0; i < 4; i++)
			roots[i]->updatePos(o);
	}
	


}

void QuadTree::updatePos(GameObject* o)
{

	if (hasObject(o))
	{
		if (isThisPart(o->getPos()))
		{
			if (!roots[0])
				return;
			
			for (int i = 0; i < 4; i++)
				roots[i]->updatePos(o);
			
		}
		else
		{
			removeObj(o);
		}
	}
	else
	{
		if (isThisPart(o->getPos()))
			addObj(o);
	}

}

void QuadTree::removeObj(GameObject* o)
{
	if (roots[0])
	{
		for (int i = 0; i < 4; i++)
			if(roots[i]->hasObject(o))
				roots[i]->removeObj(o);
	}
	objects.remove(o);
	if (objects.size() <= 8)
		closeTree();
}

bool isRectangleEqual(Rectangle r1, Rectangle r2)
{
	return r1.x == r2.x && r1.y == r2.y && r1.width == r2.width && r1.height == r2.height;
}

std::list<GameObject*> QuadTree::getObjects(Rectangle pos)
{
	std::list<GameObject*> objs;
	getObjects(objs, pos);
	return objs;
}

void QuadTree::getObjects(std::list<GameObject*>& list, Rectangle &pos)
{
	if (!roots[0])
	{
		addToList(list, pos);
		return;
	}
	if (isRectangleEqual(GetCollisionRec(this->pos, pos), this->pos))
	{
		for (auto o : objects)
			if (std::find(list.begin(), list.end(), o) == list.end())
				list.push_back(o);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (roots[i]->isThisPart(pos))
				roots[i]->getObjects(list, pos);
		}
	}
}

bool QuadTree::isThisPart(Rectangle part)
{
	return CheckCollisionRecs(pos, part);
}

void QuadTree::draw()
{
	if (roots[0])
	{
		for (int i = 0; i < 4; i++)
			roots[i]->draw();
	}
	else
	{
		DrawRectangleLinesEx(pos, 2, BLACK);
		DrawText(TextFormat("%d", objects.size()), (int)pos.x, (int)pos.y, 32, RED);
	}
}

void QuadTree::openTree()
{
	if (roots[0])
		return;
	float w = pos.width / 2;
	float h = pos.height / 2;
	if (h <= 32 || w <= 32)
		return;
	roots[0] = new QuadTree({ pos.x,pos.y,w,h });
	roots[1] = new QuadTree({ pos.x + w,pos.y,w,h });
	roots[2] = new QuadTree({ pos.x + w,pos.y + h,w,h });
	roots[3] = new QuadTree({ pos.x,pos.y + h,w,h });
	for (auto o : objects)
		for (int i = 0; i < 4; i++)
			if (CheckCollisionRecs(o->getPos(), roots[i]->pos))
				roots[i]->addObj(o);
}

void QuadTree::closeTree()
{
	if (!roots[0])
		return;
	for (int i = 0; i < 4; i++)
	{
		delete roots[i];
		roots[i] = nullptr;
	}

}

void QuadTree::addToList(std::list<GameObject*>& list, Rectangle pos)
{
	Rectangle collision = GetCollisionRec(pos, this->pos);
	if (collision.width == this->pos.width && collision.height == this->pos.height)
	{
		for (auto o : objects)
			if (std::find(list.begin(), list.end(), o) == list.end())
				list.push_back(o);
		return;
	}
	for (auto o : objects)
		if (CheckCollisionRecs(o->getPos(), pos) && std::find(list.begin(), list.end(), o) == list.end())
			list.push_back(o);
}

bool QuadTree::hasObject(GameObject* o)
{
	return std::find(objects.begin(), objects.end(), o) != objects.end();
}