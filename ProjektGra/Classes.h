#pragma once

#include<SFML/Graphics.hpp>
#include<random>
using namespace sf;
using namespace std;

// globalne

const double TIME_PER_FRAME = 0.167;
const Vector2u SCREEN_SIZE(1600u, 900u);

//

class InputAction
{
public:
	Keyboard::Key key;
	bool multi_press;
	

};

class GameObject
{
public:
	Vector2f position;
	Sprite* sprite;
};

class Timer
{
private:
	float max_time;
	float current_time;

	bool reset;

	void (*function)();

public:
	void tick();
	Timer();
	Timer(float, void (*)(), bool);
	~Timer();
};

void print(string);

int random_number(int, int);

Sprite* generate_sprite(Texture*);