#include "BossEnterWall.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "../Game.h"
#include "SpawnPoint.h"
#include "../../Core/WaveCollapsFun.h"

BossEnterWall::BossEnterWall(float x, float y, float w, float h)
{
    solidObject = true;
	moving = false;
	pos = Rectangle{ x, y, w, h };
    mass = 1000;
    collisionElemnets.push_back(new CollisionElementBox({ 0, 0, pos.width, pos.height }));
}

void BossEnterWall::start()
{
    Rectangle getPos;
    getPos.width = 300;
    getPos.height = 300;
    getPos.x = pos.x + pos.width / 2 - getPos.width / 2;
    getPos.y = pos.y + pos.height / 2 - getPos.height / 2;
    std::list<GameObject*> gms = Game::getObjects(getPos);
    for (auto o : gms)
    {
        if (o->getType() != ObjectType::SpawnPoint)
            continue;
        SpawnPoint* sp = dynamic_cast<SpawnPoint*>(o);
        if (!sp)
            continue;
        if (sp->getType() != BlockType::PlayerSpawnPoint)
            continue;
        Rectangle p = sp->getPos();
        hasSpawnPoint = true;
        spawnPoint = { p.x + p.width / 2,p.y + p.height / 2 };
        return;
    }
}

void BossEnterWall::draw() {
    DrawRectangleRec(pos, RED);
    DrawRectangleLinesEx(pos, 3, BLACK);
}

void BossEnterWall::onCollisionEnter(Collider* collider)
{
    GameObject* gm = collider->getThisObj();
    if (!gm || gm->getType() != ObjectType::Player)
        return;
    if(hasSpawnPoint)
        gm->setPos(spawnPoint);
    printf("KURWA\n");

}