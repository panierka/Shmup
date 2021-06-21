#pragma once

#include"Classes.h"

class WaveUnit;
enum Stat;

class WaveSpawner
{
public:
	static std::vector<void(*)()> big_enemies;
	static std::vector<void(*)()> small_enemies;
	static void(*boss)();

	bool intermission = false;

private:
	float time_to_spawn;
	int inwave_index;

	bool active;

	int current_wave = -1;
	int enemy_counts_per_wave[5] = {1, 1, 1, 1, 1}; //{ 7, 14, 19, 25, 33 };

	int enemies_alive = 0;

	std::vector<std::shared_ptr<WaveUnit>> wave_data;

	std::vector<Stat> possible_stats{};

public:
	WaveSpawner();
	~WaveSpawner();

	void next_wave();

	void set_wave(int n);
	void spawn(float dt);

	void change_enemies_alive(int i);

	void check_upgrade();
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

