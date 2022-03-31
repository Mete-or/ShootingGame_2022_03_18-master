#include "framework.h"
#include "ShootingGame.h"

void Random::Init()
{
	srand(time(nullptr));
}

int Random::Range(int min, int max)
{
	int r  = rand() % (max - min) + min;
	return r;
}
