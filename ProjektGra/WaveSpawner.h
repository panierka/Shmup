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

	// przerwa mi�dzy falami na ulepszenie (i z�apanie oddechu)
	bool intermission = false;

private:
	// czas do stworzenia nast�pnego wroga
	float time_to_spawn;

	// indeks aktualnie tworzonego wroga ze zbioru na dan� fal�
	int inwave_index;

	// czy tworzy
	bool active;

	int current_wave = -1;
	int enemy_counts_per_wave[5] = { 7, 14, 19, 25, 33 };

	int enemies_alive = 0;

	// "tasowalny" wektor kolejnych wrog�w w fali
	std::vector<std::shared_ptr<WaveUnit>> wave_data;

	// "tasowalny" wektor ulepsze� w tej rundzie
	std::vector<Stat> possible_stats{};

public:
	WaveSpawner();
	~WaveSpawner();

	void next_wave();

	void set_wave(int n);

	// sprawdzenie, czy mo�e si� stworzy� przeciwnik, stworzenie go je�li tak
	void spawn(float dt);

	void change_enemies_alive(int i);

	// sprawd�, jakie ulepszenie wybra� gracz na koniec przerwy mi�dzyfalowej
	void check_upgrade();
};

// pomocnicza klasa, kt�ra przechowuje informacje o tym czy wr�g jest du�y i jaki ma by� jego przypisany czas tworzenia
class WaveUnit
{
public:

	bool big;
	float dt_mod;

	WaveUnit();
	WaveUnit(bool, float);
};

