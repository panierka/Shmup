#pragma once
#include"Classes.h"

class Timer;
class PhysicalObject;
class Character;

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

class AnimationClip : public Callable
{
private:
	unsigned int starting_index;
	unsigned int frames;

	unsigned int current_frame;

public:
	const std::shared_ptr<PhysicalObject>& obj;
	bool idle;
	Timer* timer;

	//float frames_per_second;
	
public:
	virtual void function();

public:
	AnimationClip(int s_i, int f, float _fps, const std::shared_ptr<PhysicalObject>&, bool);
	~AnimationClip();

	void call();
};

