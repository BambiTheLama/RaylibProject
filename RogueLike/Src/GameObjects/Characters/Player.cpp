#include "Player.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementCircle.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"
#include "../Items/Item.h"
#include "../../Core/Controller/KeyBoardController.h"
#include "../../Core/Controller/GamePadController.h"

Player::Player(float x, float y){

    pos = {(float) x, (float) y, 48, 48};
    pos.x -= pos.width / 2;
    pos.y -= pos.height / 2;
    std::vector<Vector2> col{
        {pos.width / 4,					pos.height / 4},
        {pos.width / 4 + pos.width / 2,	pos.height / 4},
        {pos.width / 4 + pos.width / 2,	pos.height / 4 + pos.height / 2},
        {pos.width / 4,					pos.height / 4 + pos.height / 2}
    };
    collisionElemnets.push_back(new CollisionElementLines(col));
    reactOnlyToSolid = true;
    //drawOrder = 10;
    type = ObjectType::Player;
    mass = 10;
    trigger = false;
    inventory = Inventory(this);
    const int weapons = 5;
    std::string strings[5] = { "Axe","Sword","Pickaxe","Bow","Arrow" };
    for (int i = 0; i < weapons; i++)
        inventory.addItem(dynamic_cast<Item*>(new Sword(this, strings[i], 0)));
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
    case Input::Attack1:
        //weapon->use(cursorDir, deltaTime);
        inventory.use(useDir, deltaTime);
        break;
    case Input::Attack2:
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
    std::list<GameObject*> gms = Game::getObjects(pos);
    gms.remove(this);
    for (GameObject* o : gms)
    {
        Item* i = dynamic_cast<Item*>(o);
        if (!i)
            continue;
        if (inventory.addItem(i))
        {
            printf("DODA£EM ITEM\n");
        }
    }
}