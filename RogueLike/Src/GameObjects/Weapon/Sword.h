#pragma once
#include "Weapon.h"
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "WeaponStats.h"
#include "../Items/Item.h"



class Sword:public GameObject,public Weapon,public Collider,public Item
{
	std::vector<Vector2> points;
	float reloadTime = 0.0f;
	float useTime = 0.0f;
	float useTimeMax = 0.0f;
	float addLineTimer = 0.0f;
	const float addLineTimerMax = 0.02f;
	float lastAngle = 0.0f;
	const float angleDiffMax = 1.0f;
	int numberOfUse = 0;
	bool hasDefineNumberOfUse = false;
	int numberOfUseMax = 1;
	float rangeScale = 1.0f;
	float rotationAgnel = 1.0f;
	bool hasOwnRotationAngle = false;
	bool used = false;
	bool left = false;
	bool flipHorizontal = false;
	bool flipHorizontalFromFile = false;
	bool flipVertical = false;
	bool isRangeScale = false;
	float lastScaleRange = 1.0f;
	Vector2 faceingDir = { 0,0 };
public:
#pragma region Constructor
	Sword(std::string weaponType = "", int variant = 0, nlohmann::json data = nlohmann::json(), int weaponTier = 0);

	~Sword();
#pragma endregion Constructor

	void start();

	void update(float deltaTime) override;

	void update(float deltaTime, Vector2 dir) override;

	void use(Vector2 dir, float deltaTime) override;

	void onTriggerEnter(Collider* collider) override;

#pragma region DrawFun
	void draw(Rectangle pos,Color c);

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

	virtual bool getIsUpdate() { return owner; }
#pragma endregion Getters

private:

	void updateWeaponSize();

	void scaleWeapon(float scale);

	float getWeaponRotation();
protected:

	void readFromWeaponData(std::string weaponType, int variant = 0);
};

