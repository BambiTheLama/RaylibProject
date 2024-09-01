#include "Random.h"
#include <random>
#include <assert.h>
#include <math.h>

int getRandom(int& seed, int min, int max)
{
	if (min >= max)
		return min;

	seed = (std::abs(seed) * 38261 + 58243) % 93871;
	float procent = std::abs(seed) / 93871.0f;
	int v = min + (max - min) * (procent);
	return std::clamp(v, min, max - 1);
}
