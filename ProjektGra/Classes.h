#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<random>
#include "Engine.h"
#include "AnimationClip.h"
using namespace sf;
using namespace std;

class Callable;
class Timer;
class AnimationClip;
class Engine;

// "globalne"

const Vector2u SCREEN_SIZE(700u, 950u); // ekran w pikselach
const float ONE_UNIT_SIZE = 50.f; // jedna jednostka rozmiaru

//


// podstawowy obiekt istniej�cy w grze: porusza si� i ma jak�� grafik�
class GameObject
{
public:
	Vector2f position;
	Sprite* sprite;

private:
	// poruszanie si�

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

Vector2i operator*(Vector2i, Vector2i);
Vector2i operator/(Vector2i, Vector2i);

// gameobject oddzia�uj�cy na inne i z animacj�
class PhysicalObject : public GameObject
{
public:
	AnimationClip** animations;
	bool ready_to_action;
	// 0 - nic, 1 - gracz, 2 - pocisk gracza, 3 - pocisk wroga, 4 - wr�g
	int collision_marker;

private:

	Vector2i texture_size;
	Vector2i frame_size;
	int texture_coords_size_x;

public:
	PhysicalObject(Vector2f v, Sprite* s, bool b, Vector2i);
	void collide(PhysicalObject& physical_object);
	void change_sprite(int);
	void call_animation(int);
};

// pocisk
class Projectile : public PhysicalObject
{
private:
	int damage;
	
	const float base_velocity = 10.f;
	
public:
	Projectile(Vector2f pos, Sprite* s, Vector2i _frame, int _damage, float _rotation, float _spd_mod, int _coll_mask, int _dir);
};

// o. fiz. ze zdrowiem i zdolno�ci� strzelania 
class Character : public PhysicalObject
{
private:
	int max_health;
	int current_health;
	Texture* textures;

public:
	float bullet_velocity_mod = 1.f;

protected:
	int facing_direction_y{};
	int projectile_collision_mask;

public:
	Character(Vector2f v, Sprite* s, bool b, Vector2i);
	void take_hit(int _amount);
	virtual void death();

protected:
	void Shoot(int _sprite_index, Vector2i _frame, int _damage, float _start_angle, float _angle_diff, int _bullets_count);
};

// posta� z cechami typowymi dla gracza
class Player : public Character
{
public:
	int collision_marker;

public:
	Player(Vector2f v, Sprite* s, bool b, Vector2i);
};

// posta� z cechami typowymi dla wroga
class Enemy : public Character
{
public:
	int collision_marker;

public:
	Enemy(Vector2f pos, Sprite* s, bool b, Vector2i frame);
};

// pomocniczy czasomierz, do aktywowania periodycznych zdarze�
class Timer
{
private:
	bool paused{};

	float max_time;
	float current_time;

	bool reset;

	Callable* call;

	size_t timers_index;

public:
	void tick(float _deltaT);
	Timer(float, Callable*, bool, bool _start_paused);

	void start();
	void pause();

	void stop();

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