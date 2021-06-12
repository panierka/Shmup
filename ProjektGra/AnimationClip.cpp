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
	obj.change_sprite(starting_index);
	timer->start();
}

AnimationClip::~AnimationClip()
{

}

AnimationClip::AnimationClip(int s_i, int f, float _fps, PhysicalObject& o, bool _idle):
	starting_index(s_i), frames(f), obj(o), current_frame(0), idle(_idle), CallableTimer(1 / _fps, this, true, !_idle)
{

}

BlinkEffect::BlinkEffect(Character* g) :
	tint_value(0.f), CallableTimer(0.15f, this, true, false)
{
	g->effect = this;
}

BlinkEffect::~BlinkEffect()
{

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
	me(_me), CallableTimer(_time, this, true, false)
{
	_me.attack_timer = this;

	if (me.attacks.size() <= 0)
	{
		print("brak zdefiniowanych atakow u przeciwnika");
	}
}

AttackTimer::~AttackTimer()
{

}

void AttackTimer::function()
{
	int _random_attack_index = random_number(0, me.attacks.size() - 1);
	me.attacks[_random_attack_index](me);
}

PlayerInvFrames::PlayerInvFrames():
	CallableTimer(0.083f * 3.f, this, true, false)
{

}

PlayerInvFrames::~PlayerInvFrames()
{

}

void PlayerInvFrames::function()
{
	InputHandler::player->invulnerable = false;
	timer->stop();
}

CallableTimer::CallableTimer(float _time, CallableTimer* _call, bool _reset, bool _paused)
{
	std::unique_ptr<Timer> t = make_unique<Timer>(_time, _call, _reset, _paused);
	timer = t.get();

	timers.push_back(std::move(t));
}

CallableTimer::~CallableTimer()
{
	// delete timer
	timer->destroy();
	timer = nullptr;
}

InvFramesCharger::InvFramesCharger() :
	CallableTimer(0.1f, this, true, false)
{
	set_ready();
}

InvFramesCharger::~InvFramesCharger()
{
	
}

void InvFramesCharger::function()
{
	if (!fully_charged)
	{
		if (current_charge < 100.f)
		{
			current_charge += charge_value;

			float f = current_charge / 100.f;

			if (f > 1.f)
			{
				f = 1.f;
			}

			DisplayHP::set_percentage(f, DisplayHP::dodge_text);
		}
		else
		{
			set_ready();
			timer->stop();
		}
	}
}

void InvFramesCharger::set_ready()
{
	current_charge = 0.f;
	fully_charged = true;
	DisplayHP::set_percentage(1.f, DisplayHP::dodge_text);
}
