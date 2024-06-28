#pragma once

struct WeaponStats
{
	float damage = 10.0f;
	float damageMultiplier = 0.0f;
	float useTime = 0.69f;
	float useTimeMultiplier = 0.0f;
	float reloadTime = 0.0f;
	float reloadTimeMultiplier = 0.0f;
	float speed = 100.0f;
	float speedMultiplier = 1.0f;
	float range = 500.0f;
	float rangeMultiplier = 0.1f;
	float angle = 180.0f;
	float knockback = 100.0f;
	float knockbackMultiplier = 0.0f;
	int countOfUse = 2;
	int	bounce = 2;
};