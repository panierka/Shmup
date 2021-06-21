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
#include "DisplayHP.h"
#include "MainMenu.h"
#include"WaveSpawner.h"

using namespace sf;
using namespace std;

class Callable;
class Timer;
class AnimationClip;
class Engine;
class BlinkEffect;
class AttackTimer;
class PlayerInvFrames;
class InvFramesCharger;
class WaveSpawner;

enum Stat;

// "globalne"

const Vector2u SCREEN_SIZE(700u, 950u); // ekran w pikselach
const Vector2u BULLET_BOUNDS_SIZE(50u, 50u);
const float ONE_UNIT_SIZE = 50.f; // jedna jednostka rozmiaru
const float RAD2DEG = 1 / 57.3f;

//
extern WaveSpawner waves;
extern Sounds sound1;
extern BackgroundMusic main_background;
extern BackgroundMusic defeat_background;
extern BackgroundMusic victory_background;
extern BackgroundMusic boss_background;
extern BackgroundMusic* wsk1;
extern BackgroundMusic* wsk2;
extern BackgroundMusic* wsk3;
extern BackgroundMusic* wsk4;
extern BackgroundMusic* tab[4];
extern std::vector<unique_ptr<Timer>> timers;

extern int game_state;

// podstawowy obiekt istniej¹cy w grze: porusza siê i ma jak¹œ grafikê
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
	// poruszanie siê
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

// gameobject oddzia³uj¹cy na inne i z animacj¹
class PhysicalObject : public GameObject
{
public:
	std::vector<AnimationClip*> animations{};
	bool ready_to_action;

	// 0 - nic, 1 - gracz, 2 - pocisk gracza, 3 - pocisk wroga, 4 - wróg
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

// o. fiz. ze zdrowiem i zdolnoœci¹ strzelania 
class Character : public PhysicalObject
{

public:
	float bullet_velocity_mod = 1.f;
	BlinkEffect* effect;
	bool invulnerable = false;
	std::string hit_sound = "hit";

protected:
	int facing_direction_y{};
	int projectile_collision_mask;

	int max_health = 0;
	int current_health = 0;

public:
	Character(Vector2f v, Sprite* s, bool b, Vector2i);
	~Character();

	void take_hit(int _amount);
	virtual void death();
	void shoot(string _tex, Vector2i _frame, int _damage, float _start_angle, float _angle_diff, int _bullets_count, int _frames, int _framerate);

	void add_max_health(int _max);

	virtual void setHP(int _amount);
	virtual void render(RenderWindow*);
};

// postaæ z cechami typowymi dla gracza
class Player : public Character
{
public:
	PlayerInvFrames* inv_frames;
	InvFramesCharger* inv_charger;

	int stat_damage = 10;
	int stat_damage_special = 4;
	float stat_speed = 6.5f;
	float stat_bullet_velocity = 1.f;

	int lifesteal = 0;

private:
	int max_ammo = 0;
	int current_ammo; 

public:
	Player(Vector2f v, Sprite* s, bool b, Vector2i);
	~Player();
	void setHP(int _amount);
	virtual Vector2f handle_borders(Vector2f);

	virtual void death();

	void add_max_ammo(int _max);

	bool try_use_ammo();
	void reload();

	void upgrade_stat(Stat s);
};

enum Stat : int
{
	HEALTH,
	DAMAGE,
	ALT_DAMAGE,
	SPEED,
	BULLET_VELOCITY,
	AMMO,
	DODGE_RECHARGE,
	LIFESTEAL 
};

// postaæ z cechami typowymi dla wroga
class Enemy : public Character
{
public:
	std::vector<void(*)(Enemy&)> attacks;
	AttackTimer* attack_timer;

	int score_value = 0;

public:
	Enemy(Vector2f pos, Sprite* s, bool b, Vector2i frame);
	~Enemy();

	virtual void collide(unique_ptr<PhysicalObject>&);
	virtual Vector2f handle_borders(Vector2f);

	float angle_to_player();
	virtual void death();
};

// pomocniczy czasomierz, do aktywowania periodycznych zdarzeñ
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

template<typename T>
T magnitude(Vector2<T> v);

// pomocnicza funkcja do szybkiego i sformatowanego wypisywania w konsoli
void print(string);

// pomocnicza funkcja generuj¹ca liczbê z zakresu [min, max]
int random_number(int min, int max);

// stworzenie sprite'a i wyœrodkowanie pivotu
Sprite* generate_sprite(Texture* _tex, Vector2f _origin);
Sprite* generate_sprite(Texture*);

// globalny przeskok w czasomierzach
void tick_timers(float);

class TextureAtlas
{
public:
	static std::map<string, Texture*> texture_atlas;

public:
	TextureAtlas();
	~TextureAtlas();

	static void update_texture_atlas(string _name, string _path);
};

