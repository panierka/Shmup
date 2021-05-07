#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<random>
using namespace sf;
using namespace std;

class Timer;

// globalne

const float TIME_PER_FRAME = 0.0167;
const Vector2u SCREEN_SIZE(1600u, 900u);

//



class GameObject
{
private:
	// poruszanie si�

	Vector2f direction;
	float travel_time;
	bool continuous;

public:
	Vector2f position;
	Sprite* sprite;

	GameObject(Vector2f, Sprite*, bool);

	void SetPosition(Vector2f);
	void SetMove(Vector2f, float);
	void ExecuteMove();
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