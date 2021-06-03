#pragma once
#include"Classes.h"

class Timer;
class PhysicalObject;

class Callable
{
public:
	virtual void function() = 0;
};

class AnimationClip : public Callable
{
private:
	unsigned int starting_index;
	unsigned int frames;

	unsigned int current_frame;

public:
	PhysicalObject* obj;
	bool idle;
	Timer* timer;

	//float frames_per_second;
	
public:
	virtual void function();

public:
	AnimationClip(int s_i, int f, float _fps, PhysicalObject*, bool);
	~AnimationClip();

	void call();
};

