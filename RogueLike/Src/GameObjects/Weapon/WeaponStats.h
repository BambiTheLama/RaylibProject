#pragma once
#include "json.hpp"
#include "raylib.hpp"

enum class StatType
{
	positive,negative,mix,neutral
};

struct WeaponStats
{
	float damage = 0.0f;
	float damageMultiplier = 0.0f;
	float useTime = 0.0f;
	float useTimeMultiplier = 0.0f;
	float reloadTime = 0.0f;
	float reloadTimeMultiplier = 0.0f;
	float speed = 0.0f;
	float speedMultiplier = 0.0f;
	float range = 0.0f;
	float rangeMultiplier = 0.0f;
	float angle = 0.0f;
	float knockback = 0.0f;
	float knockbackMultiplier = 0.0f;
	int   countOfUse = 0;
	int	  bounce = 0;
	int   pirce = 0;

	void readStats(nlohmann::json json);
	
	void readStatsFromWeapon(nlohmann::json json, int tier);
	
	void saveStats(nlohmann::json& json);

	WeaponStats& operator+=(const WeaponStats& ws);

	WeaponStats& operator-=(const WeaponStats& ws);
	
	std::string toString(bool skipZero = false, bool showProcent = false, char separator = '+');

	void draw(Rectangle pos, float textSize, bool flexBox = false, bool frame = true, std::string title = "",
		bool skipZero = false, bool colorStats = false, bool showProcent = false, char separator = '+');
	
private:

	int getNumberOflines();

	std::string getStringLine(int l, StatType& statType);

	void drawColorStats(float x, float y, float textSize, Color negative, Color positive, Color line);
};