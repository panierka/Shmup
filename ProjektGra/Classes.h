#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<random>
using namespace sf;
using namespace std;

class Timer;

// globalne

const float TIME_PER_FRAME = 0.016f;

const Vector2u SCREEN_SIZE(700u, 950u);
const float ONE_UNIT_SIZE = 50.f;

//



class GameObject
{
private:
	// poruszanie siê

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
	void ExecuteMove();
};

class Player : GameObject
{
public:
	Vector2f next_move;
};

class Timer
{
private:
	float max_time;
	float current_time;

	bool reset;

	void (*function)();

	size_t timers_index;

public:
	void tick();
	Timer();
	Timer(float, void (*)(), bool);
	~Timer();
};

void print(string);

int random_number(int, int);

Sprite* generate_sprite(Texture*);

void tick_timers();