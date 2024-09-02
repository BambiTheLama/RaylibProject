#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../../Core/Controller/AIController.h"
#include "../Projectal/ProjectalID.h"
#include "../Weapon/Weapon.h"
#include "../AddisionalTypes/LightObject.h"
class StandardEnemy :
    public GameObject,public Hitable,public Collider,public Character,public LightObject
{
    int target = 0b010010;
    float damge = 1.0f;
    float speed = 200.0f;
    float frameTimer = 0.0f;
    CharacterController controller;
    TextureController texture;
    AIController* ai;
    Vector2 dir = { 0.0f,0.0f };
    bool col = false;
    std::string animationName = "";
    float moveTimer = 0.0f;
    bool isMoving = false;
    float contactDamage = 0.0f;
    float minRangeAttack = 0.0f;
    float maxRangeAttack = 0.0f;
    Vector2 attackDir = { 0,0 };
    Vector2 spawnPoint = { 0,0 };
    Weapon* weapon = nullptr;
    Item* item = nullptr;
    bool particleActivated = true;
public:
    StandardEnemy(std::string type, nlohmann::json data, int level);

    ~StandardEnemy();

    void start() override;

    void destroy() override;

    void update(float deltaTime);

    void draw();

    void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime);

    void onCollision(Collider* collider);

    void setPos(Vector2 point) { pos.x = point.x - pos.width / 2; pos.y = point.y - pos.height / 2; }

    Vector2 getHoldPoint() { return { pos.x + spawnPoint.x,pos.y + spawnPoint.y }; }

    void destoryController();

    void onHit();

    virtual float getSpeed() { return speed; }
private:
    void readData(std::string type, nlohmann::json data, int level);
};

