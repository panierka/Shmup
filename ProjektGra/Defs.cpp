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
	if (paused)
	{
		return;
	}

	current_time += _deltaT;

	if (current_time >= max_time)
	{
		current_time = 0;
		call->function();

		if (!reset)
		{
			timers.erase(timers.begin() + timers_index);
			delete this;
		}
	}
}

Timer::Timer(float _time, Callable* _call, bool _reset, bool _start_paused) :
	max_time(_time), current_time(0), call(_call), reset(_reset), paused(true)
{
	timers_index = timers.size();
	timers.push_back(this);

	if (!_start_paused)
	{
		start();
	}
}

void Timer::start()
{
	paused = false;
}

void Timer::pause()
{
	paused = true;
}

void Timer::stop()
{
	paused = true;
	current_time = 0;
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

Vector2i operator*(Vector2i u, Vector2i v)
{
	return Vector2i(u.x * v.x, u.y * v.y);
}

Vector2i operator/(Vector2i u, Vector2i v)
{
	return Vector2i(u.x / v.x, u.y / v.y);
}

PhysicalObject::PhysicalObject(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	GameObject(v, s, b), frame_size(_frame_size), ready_to_action(true)
{
	texture_size = Vector2i(sprite->getTexture()->getSize());

	texture_coords_size_x = (texture_size / frame_size).x;

	sprite->setTextureRect(IntRect(_frame_size, Vector2i(0, 0)));
	
	// inicjowanie animacji?
}

void PhysicalObject::animation()
{
	/*int Index[8] = { 0, 1, 2, 3 };
	int X[8] = { 4, 4, 4, 4 };
	for (int i = 0; i < 4; i++)
	{
		Vector2i v = get_vector_by_uindex(Index[i], X[i]);
		sprite->setTextureRect(IntRect(v * 100, Vector2i(100, 100)));
	}*/
}


void PhysicalObject::change_sprite(int _index)
{
	Vector2i v(_index % texture_coords_size_x, _index / texture_coords_size_x);

	sprite->setTextureRect(IntRect(v * frame_size, frame_size));
}

void PhysicalObject::call_animation(int j)
{
	animations[0]->timer->stop();

	animations[j]->call();
}

Character::Character(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	PhysicalObject(v, s, b, _frame_size) {}

Player::Player(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	Character(v, s, b, _frame_size) {}

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