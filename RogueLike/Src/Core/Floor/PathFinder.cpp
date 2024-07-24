#include "PathFinder.h"
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <list>
#include "raymath.h"

static PathFinder* pathFinder;

PathFinder::PathFinder(Vector2 mapSize, Vector2 resolution)
{
	this->resolution = resolution;
	int w = mapSize.x / resolution.x;
	int h = mapSize.y / resolution.y;
	for (int y = 0; y < h; y++)
	{
		std::vector<PathFinderNode> nodes;
		for (int x = 0; x < w; x++)
		{
			nodes.push_back(PathFinderNode());
		}
		grid.push_back(nodes);
	}
	pathFinder = this;
}

int clamp(int v, int min, int max)
{
	if (v < min)
		return min;
	if (v > max)
		return max;
	return v;
}

int getGridSize(float x, float w, float resolution)
{
	if (((int)(x + w) % (int)(resolution)) > 0)
		return (x + w) / resolution + 1;
	return (x + w) / resolution;
}

void PathFinder::setStaticBlock(Rectangle pos)
{
	int x = clamp((int)(pos.x / resolution.x), 0, grid[0].size() - 1);
	int y = clamp((int)(pos.y / resolution.y), 0, grid.size() - 1);
	int w = clamp(getGridSize(pos.x, pos.width, resolution.x), 0, grid[0].size());
	int h = clamp(getGridSize(pos.y, pos.height, resolution.y), 0, grid.size());

	for (int j = y; j < h; j++)
		for (int i = x; i < w; i++)
		{
			grid[j][i].setSolid();
		}
}

void PathFinder::draw()
{
	Color nonPath = { 255,0,255,69 };
	Color path = { 0,255,0,69 };
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
		{
			Rectangle pos = { j * resolution.x, i * resolution.y, resolution.x, resolution.y };
			DrawRectangleRec(pos, grid[i][j].solidBlock ? nonPath : path);
			DrawRectangleLinesEx(pos, 2, { 0,0,0,69 });
		}


#ifdef ShowPaths
	for (auto o : paths)
	{
		Rectangle pos = { o.x * resolution.x, o.y * resolution.y, resolution.x, resolution.y };
		DrawRectangleRec(pos, RED);
		DrawRectangleLinesEx(pos, 2, BLACK);
	}
#endif // ShowPath


}

bool PathFinder::hasGridCell(int x, int y)
{
	return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size();
}

bool PathFinder::checkCell(std::list<Vector2>& toCheck, int x, int y,int comeFromX,int comeFromY)
{
	if (!hasGridCell(x, y) || grid[y][x].solidBlock)
		return false;
	for (int j = y - objSizeH / 2; j < y + objSizeH / 2; j++)
		for (int i = x - objSizeW / 2; i < x + objSizeW / 2; i++)
		{
			if (hasGridCell(i, j) && grid[j][i].solidBlock)
				return false;
		}

	if (abs(startPoint.x - x) > cellRangeX || abs(startPoint.y - y) > cellRangeY)
		return false;
	if (!grid[y][x].wasCheck)
		return true;
	return false;
	return grid[y][x].fullPath > grid[comeFromY][comeFromX].fullPath;
}

void PathFinder::updateToGoCell(int x, int y, int ex, int ey,int cost)
{
	grid[ey][ex].toGo = grid[y][x].toGo + cost;
}

int toGoConst(int x, int y, int endX, int endY)
{
	return abs((x - endX)) + abs((y - endY));
}

void PathFinder::updateToEndCell(int x, int y, int endX, int endY)
{
	grid[x][y].toEnd = toGoConst(x, y, endX, endY);
}

void PathFinder::updateCell(std::list<Vector2>& toCheck, int x, int y, int cx, int cy, int endX, int endY, int cost)
{
	if (!checkCell(toCheck, cx, cy, x, y))
		return;
	updateToGoCell(x, y, cx, cy, cost);
	updateToEndCell(cx, cy, endX, endY);
	grid[cy][cx].fromX = x;
	grid[cy][cx].fromY = y;
	grid[cy][cx].update();
	for (auto v : toCheck)
		if (cx == v.x && cy == v.y)
			return;
	toCheck.push_back({ (float)cx,(float)cy });
}

void PathFinder::checkCloseCells(std::list<Vector2>& toCheck, int x, int y, int endX, int endY)
{
	updateCell(toCheck, x, y, x, y + 1, endX, endY);
	updateCell(toCheck, x, y, x, y - 1, endX, endY);
	updateCell(toCheck, x, y, x + 1, y, endX, endY);
	updateCell(toCheck, x, y, x - 1, y, endX, endY);


	updateCell(toCheck, x, y, x + 1, y + 1, endX, endY, 14);
	updateCell(toCheck, x, y, x + 1, y - 1, endX, endY, 14);
	updateCell(toCheck, x, y, x - 1, y + 1, endX, endY, 14);
	updateCell(toCheck, x, y, x - 1, y - 1, endX, endY, 14);



}

bool sortFun(Vector2& f, Vector2& s)
{
	return pathFinder->grid[(int)f.y][(int)f.x].fullPath > pathFinder->grid[(int)s.y][(int)s.x].fullPath;
}

Vector2 PathFinder::getDirToGo(Rectangle start, Rectangle end, float range)
{
	
	int x = clamp((int)((start.x + start.width / 2 - range) / resolution.x), 1, grid[0].size() - 1);
	int y = clamp((int)((start.y + start.height / 2 - range) / resolution.y), 1, grid.size() - 1);
	int w = clamp(getGridSize(start.x + start.width / 2 - range, range * 2, resolution.x), 1, grid[0].size());
	int h = clamp(getGridSize(start.y + start.height / 2 - range, range * 2, resolution.y), 1, grid.size());

	objSizeH = start.width / resolution.x;
	objSizeW = start.height / resolution.y;

	cellRangeX = (range / resolution.x) + 1;
	cellRangeY = (range / resolution.x) + 1;

	for (int i = y; i < h; i++)
		for (int j = x; j < w; j++)
		{
			grid[i][j].wasCheck = false;
		}

	bool pathFinded = false;
	int centerStartX = clamp((int)((start.x + start.width / 2) / resolution.x), 1, grid[0].size() - 1);
	int centerStartY = clamp((int)((start.y + start.height / 2) / resolution.y), 1, grid.size() - 1);
	int centerEndX = clamp((int)((end.x + end.width / 2) / resolution.x), 1, grid[0].size() - 1);
	int centerEndY = clamp((int)((end.y + end.height / 2) / resolution.y), 1, grid.size() - 1);

	grid[centerStartY][centerStartX].toGo = 0;
	grid[centerStartY][centerStartX].toEnd = toGoConst(centerStartX, centerStartY, centerEndX, centerEndY);
	grid[centerStartY][centerStartX].update();
	grid[centerStartY][centerStartX].wasCheck = true;
	grid[centerStartY][centerStartX].fromX = -1;
	grid[centerStartY][centerStartX].fromY = -1;
	std::list<Vector2> toCheck = { {(float)centerStartX,(float)centerStartY} };
	pathFinder = this;
	startPoint = { (float)centerStartX,(float)centerStartY };
	Vector2 closest = startPoint;
	int closestV = toGoConst(centerStartX, centerStartY, centerEndX, centerEndY);
	while (toCheck.size() > 0)
	{
		Vector2 checkPoint = toCheck.back();
		toCheck.pop_back();

		if (toGoConst(checkPoint.x, checkPoint.y, centerEndX, centerEndY) < closestV)
		{
			closestV = toGoConst(checkPoint.x, checkPoint.y, centerEndX, centerEndY);
			closest = checkPoint;
		}
		if (checkPoint.x == centerEndX && checkPoint.y == centerEndY)
			break;
		checkCloseCells(toCheck, checkPoint.x, checkPoint.y, centerEndX, centerEndY);
		grid[checkPoint.y][checkPoint.x].wasCheck = true;
		toCheck.sort(sortFun);
	}
	int lastX = closest.x;
	int lastY = closest.y;
	int comefromX = 0;
	int comefromY = 0;
	while (lastX > 0 && lastY > 0)
	{
		int thisX = grid[lastY][lastX].fromX;
		int thisY = grid[lastY][lastX].fromY;
		if (thisX >= 0 && thisY >= 0)
		{
			comefromX = lastX;
			comefromY = lastY;
			paths.push_back({ (float)lastX ,(float)lastY });
		}
		lastX = thisX;
		lastY = thisY;
	}
	paths.push_back({ (float)centerStartX ,(float)centerStartY });
	return { (float)(comefromX - centerStartX),(float)(comefromY - centerStartY) };
}