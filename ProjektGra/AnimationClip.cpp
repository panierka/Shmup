#include "AnimationClip.h"

void AnimationClip::function()
{
	current_frame++;;
	
	if (current_frame < frames)
	{
		obj.change_sprite(starting_index + current_frame);
	}
	else
	{
		if (idle) 
		{
			obj.change_sprite(starting_index);
			current_frame = 0;
		}
		else 
		{
			timer->stop();
			obj.call_animation(0);
		}
	}
}

void AnimationClip::call()
{
	obj.ready_to_action = idle;

	current_frame = 0;
	obj.change_sprite(0);
	timer->start();
}

AnimationClip::~AnimationClip()
{
	// delete timer
	timer->destroy();
	timer = nullptr;
}

AnimationClip::AnimationClip(int s_i, int f, float _fps, PhysicalObject& o, bool _idle):
	starting_index(s_i), frames(f), obj(o), current_frame(0), idle(_idle)
{
	std::unique_ptr<Timer> t = make_unique<Timer>(1 / _fps, this, true, !_idle);
	timer = t.get();

	timers.push_back(std::move(t));
}

BlinkEffect::BlinkEffect(Character* g) :
	tint_value(0.f)
{
	g->effect = this;

	std::unique_ptr<Timer> t = make_unique<Timer>(0.15f, this, true, false);
	timer = t.get();

	timers.push_back(std::move(t));
}

BlinkEffect::~BlinkEffect()
{
	// delete timer
	timer->destroy();
	timer = nullptr;
}

void BlinkEffect::activate()
{
	tint_value = 1.f;
	timer->start();
}

void BlinkEffect::function()
{
	tint_value = 0.f;
	timer->stop();
}

Callable::~Callable()
{
	
}

AttackTimer::AttackTimer(float _time, Enemy& _me) :
	me(_me)
{
	if (me.attacks.size() > 0)
	{
		std::unique_ptr<Timer> t = make_unique<Timer>(_time, this, true, false);
		timer = t.get();

		timers.push_back(std::move(t));

		_me.attack_timer = this;
	}
	else
	{
		print("brak zdefiniowanych atakow u przeciwnika");
	}
}

AttackTimer::~AttackTimer()
{
	// delete timer
	timer->destroy();
	timer = nullptr;
}

void AttackTimer::function()
{
	int _random_attack_index = random_number(0, me.attacks.size() - 1);
	me.attacks[_random_attack_index](me);
}