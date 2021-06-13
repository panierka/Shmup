#pragma once

#include"Classes.h"

class WaveUnit;

class WaveSpawner
{
public:
	static std::vector<void(*)()> big_enemies;
	static std::vector<void(*)()> small_enemies;
	static void(*boss)();

private:
	float time_to_spawn;
	int inwave_index;
	bool active;

	int current_wave = -1;
	int enemy_counts_per_wave[5] = { 7, 14, 19, 25, 33 };

	std::vector<std::shared_ptr<WaveUnit>> wave_data;

public:
	WaveSpawner();
	~WaveSpawner();

	void next_wave();

	void set_wave(int n);
	void spawn(float dt);
};

class WaveUnit
{
public:

	bool big;
	float dt_mod;

	WaveUnit();
	/*WaveUnit(const WaveUnit&) = default;
	WaveUnit& operator=(const WaveUnit&) = default;*/
	WaveUnit(bool, float);
};

