#pragma once
#include"Classes.h"
#include"KeyAction.h"

class Timer;
class PhysicalObject;
class Character;
class Enemy;

class Callable
{
public:
	virtual void function() = 0;

	virtual ~Callable();
};

class CallableTimer : public Callable
{
public:
	Timer* timer = nullptr;

public:
	CallableTimer(float _time, CallableTimer* _call, bool _reset, bool _paused);
	virtual ~CallableTimer();
};

class BlinkEffect : public CallableTimer
{
public:
	float tint_value;

public:
	BlinkEffect(Character*);
	~BlinkEffect();
	void activate();

	virtual void function();
};

class AttackTimer : public CallableTimer
{
public:
	Enemy& me;

public:
	AttackTimer(float _time, Enemy& _me);
	~AttackTimer();

	virtual void function();
};

class PlayerInvFrames : public CallableTimer
{
public:
	PlayerInvFrames();
	~PlayerInvFrames();

	virtual void function();
};

class InvFramesCharger : public CallableTimer
{
public:
	bool fully_charged = false;
	int charge_value = 3;

private:
	int current_charge = 0;

public:
	InvFramesCharger();
	~InvFramesCharger();

	virtual void function();

private:
	void set_ready();
};

class AnimationClip : public CallableTimer
{
private:
	unsigned int starting_index;
	unsigned int frames;

	unsigned int current_frame;

public:
	PhysicalObject& obj;
	bool idle;

	//float frames_per_second;
	
public:
	virtual void function();

public:
	AnimationClip(int s_i, int f, float _fps, PhysicalObject&, bool);
	~AnimationClip();

	void call();
};

