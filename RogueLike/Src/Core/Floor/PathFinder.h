#pragma once
#include <vector>
#include "raylib.hpp"
#include <list>
#include <map>

#define ShowPaths

struct PathFinderNode
{
	bool solidBlock = false, wasCheck = false;
	int toGo = -1, toEnd = -1, fullPath = -1;
	int fromX = -1, fromY = -1;

	void setSolid(bool solid) { solidBlock = solid; }

	void update() { fullPath = toEnd + toGo; wasCheck = true; }
};

class PathFinder
{
	std::vector<std::vector<PathFinderNode>> grid;
	std::vector <Rectangle> toCheckPos;
	std::vector <Rectangle> toCheckPos2;
	Vector2 resolution;
	int cellRangeX = 0;
	int cellRangeY = 0;
	int objSizeW = 0;
	int objSizeH = 0;
	Vector2 startPoint = { 0,0 };
#ifdef ShowPaths
	std::list<Vector2> paths;
#endif // ShowPath


public:
	PathFinder(Vector2 mapSize = { 1,1 }, Vector2 resolution = { 1,1 });

	void setStaticBlock(Rectangle pos, bool staticBlock = true);

	void addToCheck(Rectangle toCheckPos) { this->toCheckPos.push_back(toCheckPos); }

	void update();

	void draw();
#ifdef ShowPaths
	void clearPaths() { paths.clear(); }
#endif // ShowPath
	bool hasGridCell(int x, int y);

	bool checkCell(std::list<Vector2>& toCheck, int x, int y, int comeFromX, int comeFromY);

	void updateToGoCell(int x, int y, int ex, int ey, int cost = 10);

	void updateToEndCell(int x, int y, int endX, int endY);

	void updateCell(std::list<Vector2>& toCheck, int x, int y, int cx, int cy, int endX, int endY, int cost = 10);

	void checkCloseCells(std::list<Vector2>& toCheck, int x, int y, int endX, int endY);

	bool hasPath(Rectangle start, Rectangle end);

	Vector2 getDirToGo(Rectangle start, Rectangle end, float range);

	std::list<Vector3> getPathToGo(Rectangle start, Rectangle end, float range);

	friend bool sortFun(Vector2& f, Vector2& s);
};

