#pragma once

#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include<map>
#include<random>
#include "Engine.h"
#include "AnimationClip.h"
#include<algorithm>
#include "SoundEffects.h"

using namespace sf;
using namespace std;

class Callable;
class Timer;
class AnimationClip;
class Engine;
class BlinkEffect;
class AttackTimer;
// "globalne"

const Vector2u SCREEN_SIZE(700u, 950u); // ekran w pikselach
const Vector2u BULLET_BOUNDS_SIZE(50u, 50u);
const float ONE_UNIT_SIZE = 50.f; // jedna jednostka rozmiaru
const float RAD2DEG = 1 / 57.3f;

//
extern Sounds sound1;
extern std::vector<unique_ptr<Timer>> timers;
extern std::map<string, Texture*> texture_atlas;


// podstawowy obiekt istniej�cy w grze: porusza si� i ma jak�� grafik�
class GameObject: public std::enable_shared_from_this<GameObject>
{
public:
	Vector2f position;
	Sprite* sprite;
	std::shared_ptr<GameObject> shared_this = nullptr;

protected:
	Vector2f direction;

	bool destroy_this = false;

private:
	// poruszanie si�
	float distance;
	float travel_time;
	bool continuous;
	float time_spent_travelling{};
	bool normalize;

public:
	GameObject(Vector2f, Sprite*, bool);
	virtual ~GameObject();

	virtual void start();

	virtual void set_position(Vector2f);
	virtual Vector2f handle_borders(Vector2f);

	void set_move(Vector2f dir, float s, float t);
	void set_move(Vector2f dir, float s, float t, bool norm);
	void execute_move(float);

	virtual void render(RenderWindow*);
	virtual void destroy();
};

Vector2i operator*(Vector2i, Vector2i);
Vector2i operator/(Vector2i, Vector2i);

// gameobject oddzia�uj�cy na inne i z animacj�
class PhysicalObject : public GameObject
{
public:
	std::vector<AnimationClip*> animations{};
	bool ready_to_action;

	// 0 - nic, 1 - gracz, 2 - pocisk gracza, 3 - pocisk wroga, 4 - wr�g
	int collision_marker;
	FloatRect* collider;
	Vector2f offset;

private:

	Vector2i texture_size;
	Vector2i frame_size;
	int texture_coords_size_x;

public:
	PhysicalObject(Vector2f v, Sprite* s, bool b, Vector2i);
	virtual ~PhysicalObject();
	virtual void start();

	void create_collider(Vector2f _offset, Vector2f _size);
	virtual void collide(std::unique_ptr<PhysicalObject>& physical_object);

	void change_sprite(int);
	void call_animation(int);

	void set_position(Vector2f);
	virtual void destroy();
};

// pocisk
class Projectile : public PhysicalObject
{
private:
	int damage;
	int target_collision_mask;

	const float base_velocity = 10.f;
	
public:
	Projectile(Vector2f pos, Sprite* s, Vector2i _frame, int _damage, float _rotation, float _spd_mod, int _coll_mask, int _dir);
	~Projectile();
	virtual Vector2f handle_borders(Vector2f);

	virtual void collide(unique_ptr<PhysicalObject>&);
};

// o. fiz. ze zdrowiem i zdolno�ci� strzelania 
class Character : public PhysicalObject
{
private:
	int max_health;
	int current_health;

public:
	float bullet_velocity_mod = 1.f;
	std::vector<Texture*> textures;
	BlinkEffect* effect;

protected:
	int facing_direction_y{};
	int projectile_collision_mask;

public:
	Character(Vector2f v, Sprite* s, bool b, Vector2i);
	~Character();

	void take_hit(int _amount);
	virtual void death();
	void shoot(int _sprite_index, Vector2i _frame, int _damage, float _start_angle, float _angle_diff, int _bullets_count, int _frames, int _framerate);

	virtual void render(RenderWindow*);
};

// posta� z cechami typowymi dla gracza
class Player : public Character
{
public:
	Player(Vector2f v, Sprite* s, bool b, Vector2i);

	virtual Vector2f handle_borders(Vector2f);
};

// posta� z cechami typowymi dla wroga
class Enemy : public Character
{
public:
	std::vector<void(*)(Enemy&)> attacks;
	AttackTimer* attack_timer;

public:
	Enemy(Vector2f pos, Sprite* s, bool b, Vector2i frame);
	~Enemy();

	virtual void collide(unique_ptr<PhysicalObject>&);
	virtual Vector2f handle_borders(Vector2f);

	float angle_to_player();
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

	void destroy();

	~Timer();
};

// pomocnicza funkcja do szybkiego i sformatowanego wypisywania w konsoli
void print(string);

// pomocnicza funkcja generuj�ca liczb� z zakresu [min, max]
int random_number(int min, int max);

// stworzenie sprite'a i wy�rodkowanie pivotu
Sprite* generate_sprite(Texture* _tex, Vector2f _origin);
Sprite* generate_sprite(Texture*);

// globalny przeskok w czasomierzach
void tick_timers(float);