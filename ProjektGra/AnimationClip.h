#pragma once
#include"Classes.h"
#include"KeyAction.h"

class Timer;
class PhysicalObject;
class Character;
class Enemy;

// klasa wywo³ywalna z zewn¹trz
class Callable
{
public:
	virtual void function() = 0;

	virtual ~Callable();
};

// callable, tylko od razu zintegrowane z timerem
class CallableTimer : public Callable
{
public:
	Timer* timer = nullptr;

public:
	CallableTimer(float _time, CallableTimer* _call, bool _reset, bool _paused);
	virtual ~CallableTimer();
};

// obs³uga efektu "migania" postaci po trafieniu
class BlinkEffect : public CallableTimer
{
public:
	// na ile postaæ jest przykryta biel¹
	float tint_value;

public:
	BlinkEffect(Character*);
	~BlinkEffect();
	void activate();

	virtual void function();
};

// obs³uga losowa ataku przypisana do przeciwnika i timera z konkretnym interwa³em
class AttackTimer : public CallableTimer
{
public:
	Enemy& me;

public:
	AttackTimer(float _time, Enemy& _me);
	~AttackTimer();

	virtual void function();
};

// funkcjonalnie jest to klasa ob³uguj¹ca czas niewra¿liwoœci gracza przy uniku
class PlayerInvFrames : public CallableTimer
{
public:
	PlayerInvFrames();
	~PlayerInvFrames();

	virtual void function();
};

// obs³uga ³adowania siê akcji pod spacj¹ gracza
class InvFramesCharger : public CallableTimer
{
public:
	bool fully_charged = false;
	// o ile jest dodawane co interwa³
	float charge_value = 3.1f;

private:
	float current_charge = 0;

public:
	InvFramesCharger();
	~InvFramesCharger();

	virtual void function();

private:
	void set_ready();
};

// obs³uga jednej animacji 
class AnimationClip : public CallableTimer
{
private:
	// klatka pocz¹tkowa
	unsigned int starting_index;

	// klatki w ogóle
	unsigned int frames;

	unsigned int current_frame;

public:
	PhysicalObject& obj;
	bool idle;
	
public:
	virtual void function();

public:
	// pobiera docelowy framerate
	AnimationClip(int s_i, int f, float _fps, PhysicalObject&, bool);
	~AnimationClip();

	void call();
};

