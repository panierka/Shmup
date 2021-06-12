#pragma once

#include"Classes.h"


class WaveSpawner
{
public:
	static std::vector<void(*)()> big_enemies;
	static std::vector<void(*)()> small_enemies;

private:
	float test_timer;

public:
	WaveSpawner();
	~WaveSpawner();

	void spawn(float dt);
};

