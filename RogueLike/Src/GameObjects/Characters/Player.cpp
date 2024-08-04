#include "Player.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementCircle.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"
#include "../Items/Item.h"
#include "../../Core/Controller/KeyBoardController.h"
#include "../../Core/Controller/GamePadController.h"
#include "Wall.h"
#include "../Projectal/Bomb.h"
#include "../AddisionalTypes/Interactive.h"
#include "../Items/ItemFactory.h"

Player::Player(float x, float y):Hitable(100.0f){

    pos = {(float) x, (float) y, 48, 48};
    pos.x -= pos.width / 2;
    pos.y -= pos.height / 2;
    std::vector<Vector2> col{
        {pos.width / 4,					pos.height / 4},
        {pos.width / 4 + pos.width / 2,	pos.height / 4},
        {pos.width / 4 + pos.width / 2,	pos.height / 4 + pos.height / 2},
        {pos.width / 4,					pos.height / 4 + pos.height / 2}
    };
    addCollisionElement(new CollisionElementLines(col));
    //reactOnlyToSolid = true;
    //drawOrder = 10;
    type = ObjectType::Player;
    mass = 1000;
    trigger = false;
    inventory = Inventory(this);
    ///*

    Weapon* w = getWeapon(0, 0, WeaponType::Axe);
    Item* i = dynamic_cast<Item*>(w);
    if (i && !inventory.addItem(i) && w)
        delete w;
    w = getWeapon(0, 0, WeaponType::Bow);
    i = dynamic_cast<Item*>(w);
    if (i && !inventory.addItem(i) && w)
        delete w;
    w = getWeapon(0, 0, WeaponType::Sword);
    i = dynamic_cast<Item*>(w);
    if (i && !inventory.addItem(i) && w)
        delete w;
    //*/
    for (int j = 0; j < 8; j++)
    {
        Item* i2 = getWeaponNode(0);
        if (i2 && !inventory.addItem(i2))
            delete i2;
    }

}

Player::~Player() {

}

void Player::start() {

}

void Player::update(float deltaTime) {
    Hitable::update(deltaTime);
    inventory.update(deltaTime);
    inventory.updateClick();
    timer += deltaTime;
    timer -= (float)((int)(timer / 1) * 1);
    updateCloseInteractive();
    if (IsKeyPressed(KEY_F5))
    {
        Controller* c;
        if (!setController(c = new KeyBoardController()))
            delete c;
    }
    if (IsKeyPressed(KEY_F6))
    {
        Controller* c;
        if (!setController(c = new GamePadController()))
            delete c;
    }
    


}

void Player::updateCloseInteractive()
{
    if (closeObj)
        closeObj->setIsClosesObject(false);

    closeObj = getCloseInteractiveObjects();

    if (closeObj)
        closeObj->setIsClosesObject(true);
}

void Player::move(Vector2 dir, float deltaTime) {
    if (!inventory.isDescriptionShowed())
    {
        pos.x += dir.x * deltaTime * speed;
        pos.y += dir.y * deltaTime * speed;
    }
    inventory.update(0.0f);
}

void Player::action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime) {
    if (cursorDir.x != 0.0f || cursorDir.y != 0.0f)
        useDir = Vector2Normalize(cursorDir);
    switch (input)
    {
    case Input::Attack:
        //weapon->use(cursorDir, deltaTime);
        inventory.use(useDir, deltaTime);
        break;
    case Input::StopAttack:
        inventory.stopUse(useDir, deltaTime);
        break;
    case Input::Bomb:
        Game::addObject(new Bomb(pos.x + pos.width / 2 + cursorDir.x * 50, pos.y + pos.height / 2 + cursorDir.y * 50));
        break;
    case Input::IDE:
        break;
    case Input::NextItem:
        if (!inventory.isDescriptionShowed())
            inventory.nextItem(false);
        break;
    case Input::PrivItem:
        if (!inventory.isDescriptionShowed())
            inventory.privItem(false);
        break;
    case Input::SwapDescriptionVisible:
        inventory.swapVisibleDescriptions();
        break;
    case Input::Interact:
        if (inventory.isDescriptionShowed())
            inventory.setItemToHand();
        else
            interact();
        break;

    case Input::NextSlot:
        if (inventory.isDescriptionShowed())
            inventory.nextSlot();
        break;
    case Input::PrivSlot:
        if (inventory.isDescriptionShowed())
            inventory.privSlot();
        break;
    case Input::UpSlot:
        if (inventory.isDescriptionShowed())
            inventory.upSlot();
        break;
    case Input::DownSlot:
        if (inventory.isDescriptionShowed())
            inventory.downSlot();
        break;
    case Input::DropItem:
        if (!inventory.isDescriptionShowed())
            inventory.dropItem();
    default:
        break;
    }
}

void Player::draw() {
    DrawFrameRec(pos, BLUE, BLACK);
    Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });

    float range = 50.0f;
    float rangeMax = inventory.getRange();
    const int minSegments = 5;

    int segments = (int)(rangeMax / (2 * range));

    if (segments < minSegments)
    {
        segments = minSegments;
        range = rangeMax / (2 * segments);
    }

    Vector2 starLine = { pos.x + pos.width / 2,pos.y + pos.height / 2 };

    DrawSegmentLine(starLine, useDir, 10, timer*3, rangeMax, segments, BLACK);

}

void Player::drawUI()
{
    inventory.draw();
}

void Player::onCollisionEnter(Collider* collider) { 
    Character* ch = dynamic_cast<Character*>(collider);
    Hitable* hit = dynamic_cast<Hitable*>(collider);
    //if (hit)
    //{
    //    hit->dealDamage(2);
    //}
    //if (ch)
    //    ch->destoryController();
}

void Player::onCollisionExit(Collider* collider) {

}

void Player::interact()
{
    Interactive* interactObj = getCloseInteractiveObjects();
    if (interactObj)
        interactObj->interact(this);
}

Interactive* Player::getCloseInteractiveObjects()
{
    std::list<GameObject*> gms = Game::getObjects(RectangleIncreasSize(pos, 40));
    Interactive* interactObj = nullptr;
    float minDist = 0.0f;
    gms.remove(this);
    for (GameObject* o : gms)
    {
        Interactive* iObj = dynamic_cast<Interactive*>(o);
        if (!iObj)
            continue;
        Item* item = dynamic_cast<Item*>(o);
        if (item && inventory.hasThisItem(item))
            continue;
        if (interactObj)
        {
            float tmpMinDist = Vector2Distance(getMidlePoint(getPos()), getMidlePoint(o->getPos()));
            if (tmpMinDist < minDist)
            {
                minDist = tmpMinDist;
                interactObj = iObj;
            }
        }
        else
        {
            minDist = Vector2Distance(getMidlePoint(getPos()), getMidlePoint(o->getPos()));
            interactObj = iObj;
        }

    }
    

    return interactObj;
}
