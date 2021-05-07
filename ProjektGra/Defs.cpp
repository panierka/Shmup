#include"Classes.h";
#include<iostream> // debug only

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

void Timer::tick()
{
	current_time += TIME_PER_FRAME;

	if (current_time >= max_time)
	{
		current_time = 0;
		function();

		if (!reset)
		{
			delete this;
		}
	}
}

Timer::Timer():
	max_time(1), current_time(0),  function(nullptr), reset(false) 
{
	print("ERROR: pusty timer, tak nie wolno");
}

Timer::Timer(float _time, void (*f)(), bool _reset):
	max_time(_time), current_time(0), function(f), reset(_reset) {}

Timer::~Timer()
{

}