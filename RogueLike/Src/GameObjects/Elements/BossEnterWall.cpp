#include "BossEnterWall.h"
#include "../Game.h"
#include "SpawnPoint.h"
#include "../../Core/WaveCollapsFun.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../Collider/CollisionElementLines.h"
#include "raymath.h"

bool BossEnterWall::wasEnter = false;
bool BossEnterWall::openDoor = false;

BossEnterWall::BossEnterWall(float x, float y, float w, float h)
{
    solidObject = true;
	moving = false;
	pos = Rectangle{ x, y, w, h };
    mass = 1000;
    addCollisionElement(new CollisionElementLines({0,0,pos.width,pos.height}));
    type = ObjectType::Wall;
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
    DrawRectangleRec(pos, PURPLE);
    DrawRectangleLinesEx(pos, 2, BLACK);
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
    ControllAction* action4 = new ControllAction;
    ControllAction* action5 = new ControllAction;
    float speed = gm->getSpeed() * 200;
    Rectangle pos = gm->getPos();
    Vector2 gmPoint = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
    float dist = Vector2Distance(spawnPoint, gmPoint);

    action1->action = Action::ForcesOff;
    action1->nextAcction = action2;

    action2->action = Action::TrigerOn;
    action2->nextAcction = action3;

    action3->time = dist / speed;
    action3->dir = Vector2Normalize(Vector2Subtract(spawnPoint, gmPoint));
    action3->action = Action::GoTo;
    action3->nextAcction = action4;

    action4->action = Action::TrigerOff;
    action4->nextAcction = action5;

    action5->action = Action::ForcesOn;

    if (!controller->setControllAction(action1))
    {
        delete action1;
        delete action2;
        delete action3;
        delete action4;
        delete action5;
    }
    wasEnter = true;

}