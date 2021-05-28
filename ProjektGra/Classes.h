#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<random>
using namespace sf;
using namespace std;

class Timer;

// "globalne"

const Vector2u SCREEN_SIZE(700u, 950u); // ekran w pikselach
const float ONE_UNIT_SIZE = 50.f; // jedna jednostka rozmiaru

//


// podstawowy obiekt istniej�cy w grze: porusza si� i ma jak�� grafik�
class GameObject
{
private:
	// poruszanie si�

	Vector2f direction;
	float distance;
	float travel_time;
	bool continuous;
	float time_spent_travelling{};

public:
	Vector2f position;
	Sprite* sprite;

	GameObject(Vector2f, Sprite*, bool);
	~GameObject();

	void SetPosition(Vector2f);
	void SetMove(Vector2f, float, float);
	void ExecuteMove(float);
};

class Player : GameObject
{
public:
	Vector2f next_move;
};

// pomocniczy czasomierz, do aktywowania periodycznych zdarze�
class Timer
{
private:
	float max_time;
	float current_time;

	bool reset;

	void (*function)();

	size_t timers_index;

public:
	void tick(float _deltaT);
	Timer();
	Timer(float, void (*)(), bool);
	~Timer();
};

// pomocnicza funkcja do szybkiego i sformatowanego wypisywania w konsoli
void print(string);

// pomocnicza funkcja generuj�ca liczb� z zakresu [min, max]
int random_number(int min, int max);

// stworzenie sprite'a i wy�rodkowanie pivotu
Sprite* generate_sprite(Texture*);

// globalny przeskok w czasomierzach
void tick_timers(float);