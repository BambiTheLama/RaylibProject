#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Character.h"
#include "../AddisionalTypes/CharacterController.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Hitable.h"
#include "../../Core/Controller/AIController.h"
#include "../Projectal/ProjectalID.h"
#include "../Weapon/WeaponStats.h"

class StandardEnemy :
    public GameObject,public Hitable,public Collider,public Character
{
    int target = 0b110;
    float damge = 1.0f;
    float attackTime = 0.0f;
    float attackTimeMax = 1.0f;
    float recoveryTime = 0;
    float recoveryTimeMax = 0.5;
    float speed = 200.0f;
    float frameTimer = 0.0f;
    const float timePerFrame = 0.1f;
    Vector2 attackDir = { 0.0f,0.0f };
    CharacterController controller;
    TextureController texture;
    AIController* ai;
    Vector2 dir = { 0.0f,0.0f };
    bool col = false;
    std::string animationName = "";
    bool spawn = false;
    float contactDamage = 0.0f;
    float attackCDR = 0.0f;
    float minRangeAttack = 0.0f;
    float maxRangeAttack = 0.0f;
    ProjectalID spawnID=ProjectalID::Rock;
    WeaponStats ws;
public:
    StandardEnemy(std::string type, nlohmann::json data, int level);

    void destroy();

    void update(float deltaTime);

    void draw();

    void action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime);

    void onCollision(Collider* collider);

    void setPos(Vector2 point) { pos.x = point.x - pos.width / 2; pos.y = point.y - pos.height / 2; }

    void destoryController();

    void onHit();

    virtual float getSpeed() { return speed; }
private:
    void readData(std::string type, nlohmann::json data, int level);
};

