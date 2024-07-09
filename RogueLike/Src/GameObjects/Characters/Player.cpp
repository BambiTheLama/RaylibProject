#include "Player.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementCircle.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"

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

    //drawOrder = 10;
    type = ObjectType::Player;
    mass = 10;
    Sword* s = new Sword(this, "Axe", 1);   
    weapon = s;
    Game::addObject(s);
    trigger = false;

}

Player::~Player() {

}

void Player::start() {
    weapon->update();
    invertory.addItem(dynamic_cast<Item*>(weapon));
    Game::addObject(dynamic_cast<GameObject*>(weapon));
}

void Player::update(float deltaTime) {
    Hitable::update(deltaTime);
}

void Player::move(Vector2 dir, float deltaTime) {
    pos.x += dir.x * deltaTime * speed;
    pos.y += dir.y * deltaTime * speed;
    weapon->update();
}

void Player::action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime) {
    switch (input)
    {
    case Input::Interact:
        break;
    case Input::Attack1:
        //weapon->use(cursorDir, deltaTime);
        invertory.use(cursorDir, deltaTime);
        break;
    case Input::Attack2:
        break;
    case Input::IDE:
        break;
    case Input::NextItem:
        invertory.nextItem();
        break;
    case Input::PrivItem:
        invertory.privItem();
        break;
    default:
        break;
    }
}


void Player::draw() {
    DrawRectangleRec(pos,BLUE);
    DrawRectangleLinesEx(pos, 2, BLACK);
    Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });

}

void Player::drawUI()
{
    invertory.draw();
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