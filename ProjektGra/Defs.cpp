#include"Classes.h"
#include<iostream> // debug only


vector<Timer*> timers;

// funkcja do wyznaczania d³ugoœci wektorów
template<typename T>
T magnitude(Vector2<T> v)
{
	return static_cast<T>(sqrt(pow(v.x, 2) + pow(v.y, 2)));
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

GameObject::~GameObject()
{

}

// odpowiednia pozycja dla obiektu w logice i sprite'a
void GameObject::SetPosition(Vector2f _pos)
{
	position = _pos;
	sprite->setPosition(_pos);
}

// ruch na podstawie kierunku, dystansu i czasu na jego przebycie
void GameObject::SetMove(Vector2f _direction, float _distance, float _time)
{
	// y *= -1, ¿eby by³o zgodne z tradycyjnym uk³adem wspó³rzêdnych
	_direction.y *= -1;
	direction = _direction;
	distance = _distance * ONE_UNIT_SIZE;
	travel_time = _time;
}

// wykonanie siê ruchu
void GameObject::ExecuteMove(float _deltaT)
{
	if (magnitude(direction) == 0)
	{
		return;
	}

	// nastêpuje tu równie¿ normalizowanie kierunku ruchu
	SetPosition(position + _deltaT * direction * distance /( travel_time * magnitude(direction)));

	if(!continuous)
	{ 
		time_spent_travelling += _deltaT;

		if (time_spent_travelling >= travel_time)
		{
			direction = Vector2f(0, 0);
		}
	}
}


void Timer::tick(float _deltaT)
{
	current_time += _deltaT;

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

void tick_timers(float _deltaT)
{
	for (Timer* _timer : timers)
	{
		_timer->tick(_deltaT);
	}
}

PhysicalObject::PhysicalObject(Vector2f v, Sprite* s, bool b):
	GameObject(v, s, b), tab{}
{
	animation();
}

void PhysicalObject::animation()
{
	Texture te;
	te.loadFromFile("../Assets/Player-Spritesheet.png");
	int Coordinatesx[8] = { 0, 100, 200, 300, 100, 200, 300, 0 };
	int Coordinatesy[8] = { 0, 0, 0, 0, 100, 100, 100, 200 };
	for (int i = 0; i < 8; i++)
	{
		Sprite sprite1(te, IntRect(Coordinatesx[i], Coordinatesy[i], 100, 100));
		tab[i] = sprite1;
		tab[i].setTextureRect(IntRect(Coordinatesx[i], Coordinatesy[i], 100, 100));
	}

	/*for (int i = 0; i < 4; i++)
	{
		tab[i].setTextureRect()
	}*/
}

void Character::take_hit(int _amount)
{
	current_health -= _amount;

	if (current_health <= 0)
	{
		death();
	}
}

void Character::death()
{

}