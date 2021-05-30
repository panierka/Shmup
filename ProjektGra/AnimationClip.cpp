#include "AnimationClip.h"

void AnimationClip::function()
{
	current_frame++;
	print(to_string(current_frame));

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
	current_frame = 0;
	obj->change_sprite(0);
	timer->start();
}

AnimationClip::AnimationClip(int s_i, int f, float _fps, PhysicalObject* o):
	starting_index(s_i), frames(f), current_frame(0), obj(o), idle(false)
{
	timer = new Timer(1 / _fps, this, true);
}
