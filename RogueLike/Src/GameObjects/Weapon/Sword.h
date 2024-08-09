#pragma once
#include "Weapon.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "WeaponStats.h"
#include "../Items/Item.h"



class Sword:public GameObject,public Weapon,public Collider,public Item
{
	float reloadTime = 0.0f;
	float useTime = 0.0f;
	float useTimeMax = 0.0f;
	int numberOfUse = 0;
	bool used = false;
	bool left = false;
	bool flipHorizontal = false;
public:
#pragma region Constructor
	Sword(std::string weaponType = "", int variant = 0, nlohmann::json data = nlohmann::json(), int weaponTier = 0);

	~Sword();
#pragma endregion Constructor

	void start();

	void update(float deltaTime) override;

	void use(Vector2 dir, float deltaTime) override;

	void onTriggerEnter(Collider* collider) override;

#pragma region DrawFun
	void draw(Rectangle pos);

	void draw() override;

	void drawIcon(Rectangle pos, bool onlyIcon = true, Color color = WHITE) override;
#pragma endregion DrawFun

#pragma region Setters
	virtual void setOwner(GameObject* owner);
#pragma endregion Setters

#pragma region Getters
	float getAngle() override { return angle; }

	Vector2 getRotationPoint();

	bool isUsing() { return useTime > 0; }

	bool canSwap() override { return useTime <= 0.0f && reloadTime <= 0.0f; }
#pragma endregion Getters

private:

	void updateWeaponSize();

protected:

	void readFromWeaponData(std::string weaponType, std::vector<Vector2>& col, int variant = 0);
};

