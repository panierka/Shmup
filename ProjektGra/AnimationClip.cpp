#include "AnimationClip.h"

void AnimationClip::function()
{
	current_frame++;
	
	if (current_frame < frames)
	{
		obj->change_sprite(starting_index + current_frame);
	}
	else
	{
		obj->call_animation(0);
	}
}

void AnimationClip::call()
{
	current_frame = -1;
	timer->start();
}

AnimationClip::AnimationClip(int s_i, int f, float _fps, PhysicalObject* o):
	starting_index(s_i), frames(f), current_frame(0), obj(o)
{
	timer = new Timer(1 / _fps, this, true);
}
