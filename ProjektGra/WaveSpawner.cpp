#include "WaveSpawner.h"

WaveSpawner::WaveSpawner()
{

}

WaveSpawner::~WaveSpawner()
{
	
}

void WaveSpawner::spawn(float dt)
{
	if (test_timer > 0)
	{
		test_timer -= dt;
	}
	else
	{
		test_timer = 5.f;
		big_enemies[0]();
	}
}

std::vector<void(*)()> WaveSpawner::big_enemies{};
std::vector<void(*)()> WaveSpawner::small_enemies{};