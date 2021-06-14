#include "WaveSpawner.h"

WaveSpawner::WaveSpawner():
	active(false)
{
	for (int i = 0; i < 8; i++)
	{
		possible_stats.push_back(static_cast<Stat>(i));
	}

	std::random_shuffle(possible_stats.begin(), possible_stats.end());
}

WaveSpawner::~WaveSpawner()
{
	
}

void WaveSpawner::next_wave()
{
	current_wave++;

	if (current_wave < 5)
	{
		set_wave(enemy_counts_per_wave[current_wave]);
	}
	else
	{
		boss();
	}
}

void WaveSpawner::set_wave(int n)
{
	wave_data.clear();

	int _bigs = n / 4 + 1;
	
	for (int i = 0; i < n; i++)
	{
		std::shared_ptr<WaveUnit> w = make_shared<WaveUnit>(i < _bigs, 1 + random_number(6, 16) / 10.f);

		wave_data.push_back(w);
	}

	std::random_shuffle(wave_data.begin(), wave_data.end());

	inwave_index = wave_data.size() - 1;

	time_to_spawn = wave_data[inwave_index]->dt_mod;

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
		if (wave_data[inwave_index]->big)
		{
			big_enemies[random_number(0, big_enemies.size() - 1)]();
		}
		else
		{
			small_enemies[random_number(0, small_enemies.size() - 1)]();
		}

		inwave_index--;

		if (inwave_index == 0)
		{
			print("koniec fali");
			active = false;
			return;
		}

		time_to_spawn = wave_data[inwave_index]->dt_mod;
	}
}

void WaveSpawner::change_enemies_alive(int i)
{
	enemies_alive += i;
	
	if (enemies_alive == 0 && !active)
	{
		print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

		Engine::set_stat_upgrades(possible_stats);

		intermission = true;
	}
}

void WaveSpawner::check_upgrade()
{
	if (!intermission)
	{
		return;
	}

	float _pos_x = InputHandler::player->position.x;

	int i = -1;

	if (_pos_x < 233)
	{
		i = 0;
	}
	else if (233 < _pos_x && _pos_x < 467)
	{
		i = 1;
	}
	else
	{
		i = 2;
	}

	InputHandler::player->upgrade_stat(possible_stats[i]);

	std::random_shuffle(possible_stats.begin(), possible_stats.end());

	intermission = false;
	next_wave();
}

std::vector<void(*)()> WaveSpawner::big_enemies{};
std::vector<void(*)()> WaveSpawner::small_enemies{};

void (*WaveSpawner::boss)() = 0;

WaveUnit::WaveUnit():
	big(false), dt_mod(1)
{

}

WaveUnit::WaveUnit(bool b, float d):
	big(b), dt_mod(d)
{

}
