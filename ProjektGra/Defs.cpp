#include"Classes.h";
#include<iostream> // debug only


vector<Timer*> timers;

template<typename T>
T magnitude(Vector2<T> v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void print(string _message)
{
	cout << _message << endl;
}

int random_number(int _min, int _max)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution <int> distribution(_min, _max);
	return distribution(generator);
}

Sprite* generate_sprite(Texture* _tex)
{
	Sprite* _s = new Sprite(*_tex);
	Vector2u _half = _tex->getSize() / 2u;
	_s->setOrigin((Vector2f)_half);

	return _s;
}

GameObject::GameObject(Vector2f v, Sprite* s, bool b) :
	sprite(s), continuous(b)
{
	SetPosition(v);
}

void GameObject::SetPosition(Vector2f _pos)
{
	position = _pos;
	sprite->setPosition(_pos);
}

void GameObject::SetMove(Vector2f v, float t)
{
	v.y *= -1;
	direction = v;
	travel_time = t; 
}

void GameObject::ExecuteMove()
{
	if (magnitude(direction) == 0)
	{
		return;
	}

	SetPosition(position + TIME_PER_FRAME * direction / travel_time);
}


void Timer::tick()
{
	current_time += TIME_PER_FRAME;

	if (current_time >= max_time)
	{
		current_time = 0;
		function();

		if (!reset)
		{
			timers.erase(timers.begin() + timers_index);
			delete this;
		}
	}
}

Timer::Timer():
	max_time(1), current_time(0),  function(nullptr), reset(false), timers_index(-1)
{
	print("ERROR: pusty timer, tak nie wolno");
}

Timer::Timer(float _time, void (*f)(), bool _reset):
	max_time(_time), current_time(0), function(f), reset(_reset) 
{
	timers_index = timers.size();
	timers.push_back(this);
}

Timer::~Timer()
{

}

void tick_timers()
{
	for (Timer* _timer : timers)
	{
		_timer->tick();
	}
}