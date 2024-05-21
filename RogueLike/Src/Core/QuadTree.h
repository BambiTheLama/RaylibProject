#pragma once
#include "../GameObjects/GameObject.h"
#include <list>

class QuadTree
{
	Rectangle pos;
	std::list<GameObject*> objects;
	QuadTree* roots[4];
public:
	QuadTree(Rectangle pos);

	void addObj(GameObject* o);

	void update();

	void updatePos(GameObject* o);

	void removeObj(GameObject* o);

	std::list<GameObject*> getObjects(Rectangle pos);

	void draw();

private:
	void getObjects(std::list<GameObject*>& list, Rectangle &pos);

	void openTree();

	void closeTree();

	bool isThisPart(Rectangle part);

	void addToList(std::list<GameObject*>& list, Rectangle pos);

	bool hasObject(GameObject* o);

};

