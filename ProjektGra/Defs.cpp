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
	Engine::objects.push_back(this);
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
	GameObject(v, s, b), frame_size(_frame_size), ready_to_action(true), collision_marker(0)
{
	texture_size = Vector2i(sprite->getTexture()->getSize());

	texture_coords_size_x = (texture_size / frame_size).x;

	sprite->setTextureRect(IntRect(Vector2i(0, 0), frame_size));

	// inicjowanie animacji?

	Engine::phy_objects.push_back(this);
}

void PhysicalObject::create_collider(Vector2f _offset, Vector2f _size)
{
	collider = new FloatRect(Vector2f(0, 0), _size);
	offset = _offset;
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

void PhysicalObject::SetPosition(Vector2f _position)
{
	GameObject::SetPosition(_position);

	collider->left = position.x + offset.x;
	collider->top = position.y - offset.y;  // ???????????????????
}

Character::Character(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	PhysicalObject(v, s, b, _frame_size) {}

Player::Player(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	Character(v, s, b, _frame_size)
{
	collision_marker = 1;
	facing_direction_y = 1;
	projectile_collision_mask = 2;
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

void Character::shoot(int _sprite_index, Vector2i _frame, int _damage, float _start_angle, float _angle_diff, int _bullets_count)
{
	for (int i = 0; i < _bullets_count; i++)
	{
		Projectile* p = new Projectile(position, generate_sprite(&textures[_sprite_index]), _frame, _damage, _start_angle + i * _angle_diff, bullet_velocity_mod, projectile_collision_mask, facing_direction_y);
	}
}


void PhysicalObject::collide(PhysicalObject *coll)
{

	//FloatRect participant1 = collider->getGlobalBounds();
	//FloatRect participant2 = coll->collider->getGlobalBounds();

	if (collider->intersects(*coll->collider))
	{
		switch (coll->collision_marker)
		{
		case (1): // gracz
			print("kolizja");
			break;
		case (2): // pocisk gracza
			print("kolizja");
			break;
		case (3): // pocisk wroga
			print("kolizja");
			break;
		case (4): // wróg
			print("kolizja");
			break;
		default:
			break;
		}
	}
}

Enemy::Enemy(Vector2f pos, Sprite* s, bool b, Vector2i frame):
	Character(pos, s, b, frame)
{
	collision_marker = 4;
	facing_direction_y = -1;
	projectile_collision_mask = 3;
}

Projectile::Projectile(Vector2f pos, Sprite* s, Vector2i _frame, int _damage, float _rotation, float _spd_mod, int _coll_mask, int _dir):
	PhysicalObject(pos, s, true, _frame), damage(_damage)
{
	double proper_angle = _rotation / 57.3;
	SetMove(Vector2f(-_dir * sin(proper_angle), _dir * cos(proper_angle)), 1.f, _spd_mod * base_velocity);
}