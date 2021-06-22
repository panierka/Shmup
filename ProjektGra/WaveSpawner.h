#pragma once

#include"Classes.h"

class WaveUnit;
enum Stat;

class WaveSpawner
{
public:
	// dane o spawnowanych wrogach w kolejnych kategoriach 

	static std::vector<void(*)()> big_enemies;
	static std::vector<void(*)()> small_enemies;
	static void(*boss)();

	// przerwa miêdzy falami na ulepszenie (i z³apanie oddechu)
	bool intermission = false;

private:
	// czas do stworzenia nastêpnego wroga
	float time_to_spawn;

	// indeks aktualnie tworzonego wroga ze zbioru na dan¹ falê
	int inwave_index;

	// czy tworzy
	bool active;

	int current_wave = -1;
	int enemy_counts_per_wave[5] = { 7, 14, 19, 25, 33 };

	int enemies_alive = 0;

	// "tasowalny" wektor kolejnych wrogów w fali
	std::vector<std::shared_ptr<WaveUnit>> wave_data;

	// "tasowalny" wektor ulepszeñ w tej rundzie
	std::vector<Stat> possible_stats{};

public:
	WaveSpawner();
	~WaveSpawner();

	void next_wave();

	void set_wave(int n);

	// sprawdzenie, czy mo¿e siê stworzyæ przeciwnik, stworzenie go jeœli tak
	void spawn(float dt);

	void change_enemies_alive(int i);

	// sprawdŸ, jakie ulepszenie wybra³ gracz na koniec przerwy miêdzyfalowej
	void check_upgrade();
};

// pomocnicza klasa, która przechowuje informacje o tym czy wróg jest du¿y i jaki ma byæ jego przypisany czas tworzenia
class WaveUnit
{
public:

	bool big;
	float dt_mod;

	WaveUnit();
	WaveUnit(bool, float);
};

