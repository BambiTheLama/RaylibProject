#pragma once
#include "json.hpp"
#include "raylib.hpp"

enum class StatType
{
	positive,negative,mix,neutral
};

struct StatFloatMulti
{
	float value = 0.0f, multiplier = 0.0f;
	bool inportant = false;

	StatFloatMulti& operator+=(const StatFloatMulti& stat);

	StatFloatMulti& operator-=(const StatFloatMulti& stat);

};
struct StatFloat
{
	float value = 0.0f;
	bool inportant = false;

	StatFloat& operator+=(const StatFloat& stat);

	StatFloat& operator-=(const StatFloat& stat);
};
struct StatInt
{
	int value = 0;
	bool inportant = false;

	StatInt& operator+=(const StatInt& stat);

	StatInt& operator-=(const StatInt& stat);
};
class WeaponStats
{
	StatFloatMulti damage, useTime, reloadTime, speed, range, knockback;
	StatFloat angle;
	StatInt countOfUse, bounce, pirce;
public:
	void readStats(nlohmann::json json);
	
	void readStatsFromWeapon(nlohmann::json json, int tier = 0);
	
	void saveStats(nlohmann::json& json);

	WeaponStats& operator+=(const WeaponStats& ws);

	WeaponStats& operator-=(const WeaponStats& ws);
	
	std::string toString(bool skipZero = false, bool showProcent = false, char separator = '+');

	float getDamage() { return damage.value; }

	float getUseTime() { return useTime.value; }

	float getReloadTime() { return reloadTime.value; }

	float getSpeed() { return speed.value; }

	float getRange() { return range.value; }

	float getKnockback() { return knockback.value; }

	float getAngle() { return angle.value; }

	int getCountOfUse() { return countOfUse.value; }

	int getBounce() { return bounce.value; }

	int getPirce() { return pirce.value; }

	friend class WeaponNode;
#pragma region DrawFun
	void draw(Rectangle pos, float textSize, bool flexBox = false, bool frame = true, std::string title = "",
		bool skipZero = false, bool colorStats = false, bool showProcent = false, char separator = '+');

private:
	void drawColorStats(float x, float y, float textSize, Color negative, Color positive, Color line);
#pragma endregion DrawFun
private:

	int getNumberOflines();

	std::string getStringLine(int l, StatType& statType);


};