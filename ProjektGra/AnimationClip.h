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

class BlinkEffect : public Callable
{
public:
	Timer* timer;
	float tint_value;

	BlinkEffect(Character*);
	~BlinkEffect();
	void activate();

	virtual void function();
};

class AttackTimer : public Callable
{
public:
	Timer* timer;
	Enemy& me;

public:
	AttackTimer(float _time, Enemy& _me);
	~AttackTimer();

	virtual void function();
};

class PlayerInvFrames : public Callable
{
public:
	Timer* timer;

public:
	PlayerInvFrames();
	~PlayerInvFrames();

	virtual void function();
};

class AnimationClip : public Callable
{
private:
	unsigned int starting_index;
	unsigned int frames;

	unsigned int current_frame;

public:
	PhysicalObject& obj;
	bool idle;
	Timer* timer;

	//float frames_per_second;
	
public:
	virtual void function();

public:
	AnimationClip(int s_i, int f, float _fps, PhysicalObject&, bool);
	~AnimationClip();

	void call();
};

