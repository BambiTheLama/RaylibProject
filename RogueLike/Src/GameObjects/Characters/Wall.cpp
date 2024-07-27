#include "Wall.h"
#include "../../Core/Floor/Room.h"
#include "rlgl.h"
#include "../Game.h"

Wall::Wall(Rectangle pos) :Wall(pos.x, pos.y, pos.width, pos.height)
{

}

Wall::Wall(float x, float y, float w, float h)
{
    solidObject = true;
    moving = false;
    mass = 10000;
    pos = { x, y, w, h };
    std::vector<Vector2> col{
    {0,         0},
    {pos.width, 0},
    {pos.width, pos.height},
    {0,         pos.height }
    };
    collisionElemnets.push_back(new CollisionElementLines(col));
    type = ObjectType::Wall;
}

Wall::~Wall()
{
}


void Wall::update(float deltaTime) {
}

void Wall::draw(){ 
    DrawRectangleRec(pos, RED);
    DrawRectangleLinesEx(pos, 1, BLACK);
}

void Wall::onCollisionEnter(Collider* collider) {
    
}

void Wall::onCollisionExit(Collider* collider){

}

std::vector<Rectangle> cutRectangleMoreAtH(Rectangle pos, Rectangle part)
{
    std::vector<Rectangle> rects;
    if (part.y > pos.y)
        rects.push_back({ pos.x,pos.y,pos.width,part.y - pos.y });
    if (part.x > pos.x)
        rects.push_back({ pos.x,part.y,part.x - pos.x,part.height });
    if (part.x + part.width < pos.x + pos.width)
        rects.push_back({ part.x + part.width,part.y,pos.x + pos.width - part.x - part.width,part.height });
    if (part.y + part.height < pos.y + pos.height)
        rects.push_back({ pos.x,part.y + part.height,pos.width,pos.y + pos.height - part.y - part.height });
    return rects;
}
std::vector<Rectangle> cutRectangleMoreAtW(Rectangle pos, Rectangle part)
{
    std::vector<Rectangle> rects;


    if (part.y > pos.y)
        rects.push_back({ part.x,pos.y,part.width,part.y - pos.y });

    if (part.x > pos.x)
        rects.push_back({ pos.x,pos.y,part.x - pos.x,pos.height });

    if (part.x + part.width < pos.x + pos.width)
        rects.push_back({ part.x + part.width,pos.y,pos.x + pos.width - part.x - part.width,pos.height });


    if (part.y + part.height < pos.y + pos.height)
        rects.push_back({ part.x,part.y + part.height,part.width,pos.y + pos.height - part.y - part.height });





    return rects;
}


std::vector<Rectangle> cutRectangles(Rectangle pos, Rectangle toCut)
{
    Rectangle part = GetCollisionRec(toCut, pos);
    if (part.width > part.height)
        return cutRectangleMoreAtW(pos, part);
    return cutRectangleMoreAtH(pos, part);
}

void Wall::deletePartWall(Rectangle toDelete)
{
    Rectangle part = GetCollisionRec(toDelete, pos);
    Game::toCheckPos(pos);
    if (part.width <= 0 || part.height <= 0)
    {
        return;
    }
    else if (part.width == pos.width && part.height == pos.height)
    {
        Game::deleteObject(this);
        return;
    }
    std::vector<Rectangle> cuted = cutRectangles(pos, toDelete);
    assert(cuted.size() > 0);
    const float removeSmollerThan = 5;
    if (cuted[0].width > removeSmollerThan || cuted[0].height > removeSmollerThan)
    {
        pos = cuted[0];
        Game::addObject(this);
        updateCollison();
    }
    else
        Game::deleteObject(this);

    for (int i = 1; i < cuted.size(); i++)
    {
        if (cuted[i].width < removeSmollerThan && cuted[i].height < removeSmollerThan)
            continue;
        Wall* w = new Wall(cuted[i]);
        if (!Game::addObject(w))
            delete w;
    }
}

void Wall::updateCollison()
{
    collisionElemnets.clear();
    std::vector<Vector2> col{
    {0,         0},
    {pos.width, 0},
    {pos.width, pos.height},
    {0,         pos.height }
    };
    collisionElemnets.push_back(new CollisionElementLines(col));
    Game::toCheckPos(pos);
}