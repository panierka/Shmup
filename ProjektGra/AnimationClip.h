#pragma once
#include"Classes.h"
#include"KeyAction.h"

class Timer;
class PhysicalObject;
class Character;
class Enemy;

// klasa wywo�ywalna z zewn�trz
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

// obs�uga efektu "migania" postaci po trafieniu
class BlinkEffect : public CallableTimer
{
public:
	// na ile posta� jest przykryta biel�
	float tint_value;

public:
	BlinkEffect(Character*);
	~BlinkEffect();
	void activate();

	virtual void function();
};

// obs�uga losowa ataku przypisana do przeciwnika i timera z konkretnym interwa�em
class AttackTimer : public CallableTimer
{
public:
	Enemy& me;

public:
	AttackTimer(float _time, Enemy& _me);
	~AttackTimer();

	virtual void function();
};

// funkcjonalnie jest to klasa ob�uguj�ca czas niewra�liwo�ci gracza przy uniku
class PlayerInvFrames : public CallableTimer
{
public:
	PlayerInvFrames();
	~PlayerInvFrames();

	virtual void function();
};

// obs�uga �adowania si� akcji pod spacj� gracza
class InvFramesCharger : public CallableTimer
{
public:
	bool fully_charged = false;
	// o ile jest dodawane co interwa�
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

// obs�uga jednej animacji 
class AnimationClip : public CallableTimer
{
private:
	// klatka pocz�tkowa
	unsigned int starting_index;

	// klatki w og�le
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

