#include "Player.h"
#include "../Collider/CollisionElementLines.h"
#include "../Collider/CollisionElementBox.h"
#include "../Collider/CollisionElementCircle.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Game.h"
#include "raymath.h"

Player::Player(float x, float y){
    pos = {(float) x, (float) y, 48, 48};
    pos.x -= pos.width / 2;
    pos.y -= pos.height / 2;
    collisionElemnets.push_back(new CollisionElementBox({ pos.width / 4, pos.height /4, pos.width/2, pos.height/2}));
    //drawOrder = 10;
    type = ObjectType::Player;
    mass = 10;
    s = new Sword(this);
    trigger = false;
    Game::addObject(s);
}

Player::~Player() {

}


void Player::update(float deltaTime) {
    Hitable::update(deltaTime);
    s->update(deltaTime);
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse = GetMousePosition();
        mouse.x -= GetScreenWidth() / 2;
        mouse.y -= GetScreenHeight() / 2;
        mouse = Vector2Normalize(mouse);
        s->use(mouse, deltaTime);
    }
   
    //if (IsKeyPressed(KEY_ONE))
    //{
    //    Rectangle pos = getPos();
    //    Vector2 mouse = GetMousePosition();
    //    mouse.x -= GetScreenWidth() / 2;
    //    mouse.y -= GetScreenHeight() / 2;
    //    addForce({ -mouse.x, -mouse.y }, 16.9f, 1.0);
    //}
}

void Player::move(Vector2 dir, float deltaTime) {
    pos.x += dir.x * deltaTime * speed;
    pos.y += dir.y * deltaTime * speed;
}

void Player::action(Input input, Vector2 dir,float deltaTime) {
}


void Player::draw() {
    DrawRectangleRec(pos,BLUE);
    DrawRectangleLinesEx(pos, 2, BLACK);
    Hitable::draw({ pos.x,pos.y - 30,pos.width,20 });
    if(s->isUsing())
        s->draw();
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