#include "AnimationClip.h"

void AnimationClip::function()
{
	current_frame++;;
	
	if (current_frame < frames)
	{
		obj->change_sprite(starting_index + current_frame);
	}
	else
	{
		if (idle) 
		{
			obj->change_sprite(starting_index);
			current_frame = 0;
		}
		else 
		{
			timer->stop();
			obj->call_animation(0);
		}
	}
}

void AnimationClip::call()
{
	obj->ready_to_action = idle;

	current_frame = 0;
	obj->change_sprite(0);
	timer->start();
}

AnimationClip::~AnimationClip()
{
	obj = nullptr;
	delete timer;
}

AnimationClip::AnimationClip(int s_i, int f, float _fps, PhysicalObject* o, bool _idle):
	starting_index(s_i), frames(f), current_frame(0), obj(o), idle(_idle)
{
	timer = new Timer(1 / _fps, this, true, !_idle);
}

BlinkEffect::BlinkEffect(Character* g) :
	tint_value(0.f)
{
	g->effect = this;
	timer = new Timer(0.1f, this, false, false);
}

BlinkEffect::~BlinkEffect()
{
	delete timer;
}

void BlinkEffect::activate()
{
	timer->start();
	tint_value = 1.f;
}

void BlinkEffect::function()
{
	timer->stop();
	tint_value = 0.f;
}

Callable::~Callable()
{
	
}