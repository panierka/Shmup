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


// podstawowy obiekt istniej¹cy w grze: porusza siê i ma jak¹œ grafikê
class GameObject
{
public:
	Vector2f position;
	Sprite* sprite;

private:
	// poruszanie siê

	Vector2f direction;
	float distance;
	float travel_time;
	bool continuous;
	float time_spent_travelling{};

public:
	GameObject(Vector2f, Sprite*, bool);
	~GameObject();

	void SetPosition(Vector2f);
	void SetMove(Vector2f, float, float);
	void ExecuteMove(float);
};

// gameobject oddzia³uj¹cy na inne i z animacj¹
class PhysicalObject : public GameObject
{
public:
	PhysicalObject(Vector2f v, Sprite* s, bool b);
	Sprite tab[8]{};
	void animation();
	Vector2i get_vector_by_uindex(int _index, int _max_x);
};

// pocisk
class Projectile : public PhysicalObject
{
private:
	int damage;
	bool enemy; // jeœli nie wrogi, to gracza
};

// o. fiz. ze zdrowiem i zdolnoœci¹ strzelania 
class Character : public PhysicalObject
{
private:
	int max_health;
	int current_health;

public:
	Character(Vector2f v, Sprite* s, bool b):PhysicalObject(v, s, b){}
	void take_hit(int _amount);
	virtual void death();
};

// postaæ z cechami typowymi dla gracza
class Player : public Character
{
public:
	Player(Vector2f v, Sprite* s, bool b) :Character(v, s, b){}
};

// postaæ z cechami typowymi dla wroga
class Enemy : public Character
{
	
};

// pomocniczy czasomierz, do aktywowania periodycznych zdarzeñ
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

// pomocnicza funkcja generuj¹ca liczbê z zakresu [min, max]
int random_number(int min, int max);

// stworzenie sprite'a i wyœrodkowanie pivotu
Sprite* generate_sprite(Texture*);

// globalny przeskok w czasomierzach
void tick_timers(float);