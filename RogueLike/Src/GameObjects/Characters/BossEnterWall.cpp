#include "BossEnterWall.h"
#include "../AddisionalTypes/Collider/CollisionElementBox.h"
#include "../Game.h"
#include "SpawnPoint.h"
#include "../../Core/WaveCollapsFun.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "raymath.h"

bool BossEnterWall::wasEnter = false;
bool BossEnterWall::openDoor = false;

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
    getPos.width = 1600;
    getPos.height = 1600;
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
    openDoor = IsKeyDown(KEY_Q);
    trigger = openDoor;
    if (openDoor)
    {
        wasEnter = false;
        return;
    }

    DrawRectangleRec(pos, RED);
    DrawRectangleLinesEx(pos, 3, BLACK);
}

void BossEnterWall::onCollisionEnter(Collider* collider)
{
    if (wasEnter)
        return;
    GameObject* gm = collider->getThisObj();
    if (!gm || gm->getType() != ObjectType::Player)
        return;
    if (!hasSpawnPoint)
        return;

    Character* ch = dynamic_cast<Character*>(gm);
    if (!ch)
        return;
    CharacterController* controller = ch->getCharacterController();
    if (!controller)
        return;
    ControllAction* action1 = new ControllAction;
    ControllAction* action2 = new ControllAction;
    ControllAction* action3 = new ControllAction;
    float speed = gm->getSpeed();
    Rectangle pos = gm->getPos();
    Vector2 gmPoint = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
    float dist = Vector2Distance(spawnPoint, gmPoint);

    action1->action = Action::TrigerOn;
    action1->nextAcction = action2;

    action2->time = dist / speed;
    action2->dir = Vector2Normalize(Vector2Subtract(spawnPoint, gmPoint));
    action2->action = Action::GoTo;
    action2->nextAcction = action3;

    action3->action = Action::TrigerOff;

    if (!controller->setControllAction(action1))
    {
        delete action1;
        delete action2;
        delete action3;
    }
    wasEnter = true;
    printf("KURWA\n");

}