#include "Math.h"
#include <random>

float CMath::Distance(const POSITION & tPos1, const POSITION & tPos2)
{
	float x, y;
	x = tPos2.x - tPos1.x;
	y = tPos2.y - tPos1.y;

	return sqrtf(x * x + y * y);
}

int CMath::RandInt()
{
	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dis(0, 99);

	return dis(gen);
}