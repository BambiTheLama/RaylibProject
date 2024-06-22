#pragma once

struct WeaponStats
{
	float damage = 1.0f;
	float damageMultiplier = 0.0f;
	float useTime = 5.0f;
	float useTimeMultiplier = 0.0f;
	float reloadTime = 0.0f;
	float reloadTimeMultiplier = 0.0f;
	float speed = 100.0f;
	float speedMultiplier = 1.0f;
	float range = 100.0f;
	float rangeMultiplier = 0.0f;
	float angle = 100.0f;
	float knockback = 100.0f;
	float knockbackMultiplier = 0.0f;
	int countOfUse = 2;
	int	 bounce = 2;
};