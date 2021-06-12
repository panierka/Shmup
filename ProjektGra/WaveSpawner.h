#pragma once

#include"Classes.h"

struct WaveUnit;

class WaveSpawner
{
public:
	static std::vector<void(*)()> big_enemies;
	static std::vector<void(*)()> small_enemies;

private:
	float time_to_spawn;
	int wave_index;
	bool active;

	std::vector<unique_ptr<WaveUnit>> wave_data;

public:
	WaveSpawner();
	~WaveSpawner();

	void set_wave(int n);
	void spawn(float dt);
};

struct WaveUnit
{
	bool big;
	float dt_mod;

	WaveUnit();
	WaveUnit(bool, float);
};

