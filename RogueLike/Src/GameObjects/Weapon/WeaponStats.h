#pragma once
#include "json.hpp"
#include "raylib.hpp"

struct WeaponStats
{
	float damage = 1.0f;
	float damageMultiplier = 1.0f;
	float useTime = 1.0f;
	float useTimeMultiplier = 1.0f;
	float reloadTime = 0.0f;
	float reloadTimeMultiplier = 1.0f;
	float speed = 100.0f;
	float speedMultiplier = 1.0f;
	float range = 100.0f;
	float rangeMultiplier = 1.0f;
	float angle = 36.0f;
	float knockback = 100.0f;
	float knockbackMultiplier = 1.0f;
	int   countOfUse = 1;
	int	  bounce = 1;
	int   pirce = 1;

	void readStats(nlohmann::json json);
	
	void readStatsFromWeapon(nlohmann::json json, int tier);
	
	void saveStats(nlohmann::json& json);

	WeaponStats& operator+=(const WeaponStats& ws);

	WeaponStats& operator-=(const WeaponStats& ws);
	
	std::string toString();

	void draw(Rectangle pos, float textSize, bool flexBox = false, bool frame = true, std::string title = "");
};