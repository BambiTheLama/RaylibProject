#include "Wall.h"
#include "../../Core/Floor/Room.h"
#include "rlgl.h"

static std::vector<Vector2> quadPos = {
    {    0, 0},
    {tileW, 0},
    {    0, tileH},
    {    0, tileH},
    {tileW, 0},
    {tileW, tileH}
};

std::vector<Vector2> Wall::wallsPos;
bool Wall::genWalls = true;

Wall::Wall(int x, int y) {
    
        
    pos = { (float)x, (float)y, tileW, tileH };
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
    solidObject = true;
    moving = false;
    mass = 10000;
    wallsPos.push_back({ pos.x,pos.y });
    genWalls = true;
}

Wall::~Wall()
{
    auto find = std::find(wallsPos.begin(), wallsPos.end(), Vector2{ pos.x,pos.y });
    if (find != wallsPos.end())
    {
        wallsPos.erase(find);
        genWalls = true;
    }
}


void Wall::update(float deltaTime) {
}

void Wall::draw(){ 
    DrawRectangleRec(pos, RED); 
    DrawRectangleLinesEx(pos,3, BLACK);
}

void Wall::drawWalls()
{
    static int vao = -1; 
    static int vbo = -1;
    static int vboI = -1;
    if (vao == -1)
    {
        vao = rlLoadVertexArray();
    }
    rlEnableVertexArray(vao);
    if (vbo == -1)
    {
        vbo = rlLoadVertexBuffer(quadPos.data(), quadPos.size() * sizeof(Vector2), false);
        rlEnableVertexBuffer(vbo);
        rlSetVertexAttribute(0, 2, sizeof(float), RL_FLOAT, false, nullptr);

    }
    if (genWalls)
    {

        if (vboI > 0)
            rlUnloadVertexBuffer(vboI);
        rlLoadVertexBuffer(wallsPos.data(), wallsPos.size() * sizeof(Vector2), false);
        rlEnableVertexBuffer(vboI);
        rlSetVertexAttribute(1, 2, sizeof(float), RL_FLOAT, false, nullptr);
        rlSetVertexAttributeDivisor(1, 1);
    }
    rlDrawVertexArrayInstanced(0, 6, wallsPos.size());

}

void Wall::onCollisionEnter(Collider* collider) {
    
}

void Wall::onCollisionExit(Collider* collider){

}