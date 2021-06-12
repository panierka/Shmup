#include "WaveSpawner.h"

WaveSpawner::WaveSpawner()
{

}

WaveSpawner::~WaveSpawner()
{
	
}

void WaveSpawner::set_wave(int n)
{
	wave_data.clear();

	int _bigs = n / 4 + 1;
	
	for (int i = 0; i < n; i++)
	{
		unique_ptr<WaveUnit> w = make_unique<WaveUnit>();
		w->big = i < _bigs;
		w->dt_mod += random_number(6, 16) / 10.f;

		wave_data.push_back(std::move(w));
	}

	std::random_shuffle(wave_data.begin(), wave_data.end());

	wave_index = wave_data.size() - 1;

	time_to_spawn = wave_data[wave_index]->dt_mod;

	active = true;
}

void WaveSpawner::spawn(float dt)
{
	if (!active)
	{
		return;
	}

	if (time_to_spawn > 0)
	{
		time_to_spawn -= dt;
	}
	else
	{
		if (wave_data[wave_index]->big)
		{
			big_enemies[random_number(0, big_enemies.size() - 1)]();
		}
		else
		{
			small_enemies[random_number(0, small_enemies.size() - 1)]();
		}

		wave_index--;

		if (wave_index == 0)
		{
			print("koniec fali");
			active = false;
			return;
		}

		time_to_spawn = wave_data[wave_index]->dt_mod;
	}
}

std::vector<void(*)()> WaveSpawner::big_enemies{};
std::vector<void(*)()> WaveSpawner::small_enemies{};

WaveUnit::WaveUnit():
	big(false), dt_mod(1)
{

}

WaveUnit::WaveUnit(bool b, float d):
	big(b), dt_mod(d)
{

}
