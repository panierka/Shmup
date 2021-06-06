#include"Classes.h"
#include<iostream> // debug only


vector<Timer*> timers;

Sounds sound1{};

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

Sprite* generate_sprite(Texture* _tex, Vector2f _origin)
{
	Sprite* _s = new Sprite(*_tex);
	_s->setOrigin(_origin);

	return _s;
}

Sprite* generate_sprite(Texture* _tex)
{
	return generate_sprite(_tex, static_cast<Vector2f>(_tex->getSize() / 2u));
}

GameObject::GameObject(Vector2f v, Sprite* s, bool b) :
	sprite(s), continuous(b)
{
	set_position(v);
	Engine::objects.push_back(this);
}

GameObject::~GameObject()
{
	print("DTOR");

	Engine::objects.erase(std::remove(Engine::objects.begin(), Engine::objects.end(), this));

	delete sprite;
}

// odpowiednia pozycja dla obiektu w logice i sprite'a
void GameObject::set_position(Vector2f _pos)
{
	position = handle_borders(_pos);

	sprite->setPosition(position);
}

Vector2f GameObject::handle_borders(Vector2f _pos)
{
	return _pos;
}

// ruch na podstawie kierunku, dystansu i czasu na jego przebycie
void GameObject::set_move(Vector2f _direction, float _distance, float _time)
{
	set_move(_direction, _distance, _time, true);
}

void GameObject::set_move(Vector2f _direction, float _distance, float _time, bool norm)
{
	// y *= -1, ¿eby by³o zgodne z tradycyjnym uk³adem wspó³rzêdnych
	_direction.y *= -1.f;
	direction = _direction;
	distance = _distance * ONE_UNIT_SIZE;
	travel_time = _time;

	normalize = norm;
}

// wykonanie siê ruchu
void GameObject::execute_move(float _deltaT)
{
	if (destroy_this)
	{
		delete this;
		return;
	}

	float mag = magnitude<float>(direction);

	if (mag == 0)
	{
		return;
	}

	// nastêpuje tu równie¿ normalizowanie kierunku ruchu

	float mod = normalize ? (travel_time * mag): 1.f;

	set_position(position + _deltaT * direction * distance / mod);

	if(!continuous)
	{ 
		time_spent_travelling += _deltaT;

		if (time_spent_travelling >= travel_time)
		{
			direction = Vector2f(0, 0);
		}
	}
}

void GameObject::render(RenderWindow* w)
{
	w->draw(*sprite);
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
	timers.erase(std::remove(timers.begin(), timers.end(), this));
	
	print("usunieto timer");
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

PhysicalObject::~PhysicalObject()
{
	print("PO: DTOR");

	Engine::phy_objects.erase(std::remove(Engine::phy_objects.begin(), Engine::phy_objects.end(), this));

	delete collider;
	
	for (auto e : animations)
	{
		delete e;
	}

	animations.clear();
}

void PhysicalObject::create_collider(Vector2f _offset, Vector2f _size)
{
	offset = _offset;
	collider = new FloatRect(position + offset, _size);
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

void PhysicalObject::set_position(Vector2f _position)
{
	GameObject::set_position(_position);
	
	collider->left = position.x + offset.x;
	collider->top = position.y + offset.y;  // ???????????????????
}

Character::Character(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	PhysicalObject(v, s, b, _frame_size) 
{
	effect = new BlinkEffect(this);
}

Character::~Character()
{
	delete effect;

	for (auto t : textures)
	{
		delete t;
	}

	textures.clear();
}

Player::Player(Vector2f v, Sprite* s, bool b, Vector2i _frame_size):
	Character(v, s, b, _frame_size)
{
	collision_marker = 1;
	facing_direction_y = 1;
	projectile_collision_mask = 2;
	bullet_velocity_mod = 1.5f;
}

Vector2f Player::handle_borders(Vector2f _pos)
{
	float _off0 = collider->width / 2.f - offset.x;
	float _off = collider->width / 2.f + offset.x;

	if (_pos.x - _off0 < 0)
	{
		_pos.x = _off0;
	}
	else if (_pos.x + _off > SCREEN_SIZE.x)
	{
		_pos.x = -_off + SCREEN_SIZE.x;
	}

	return _pos;
}

void Character::take_hit(int _amount)
{
	current_health -= _amount;

	effect->activate();

	return;

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
		float _angle = _start_angle + (i * _angle_diff);
		Projectile* p = new Projectile(position, generate_sprite(textures[_sprite_index], Vector2f(12.f, 25.f)), _frame, _damage, _angle, bullet_velocity_mod, projectile_collision_mask, facing_direction_y);

		p->animations.push_back(new AnimationClip(0, 4, 24, p, true));

		p->create_collider(Vector2f(0.f, 0.f), Vector2f(_frame));

		p->sprite->setRotation(-_angle);
	}
}

void Character::render(RenderWindow* w)
{
	Engine::shader.setUniform("tint", effect->tint_value);

	w->draw(*sprite, &Engine::shader);
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
			print("kolizja - gracz");
			break;
		case (2): // pocisk gracza
			print("kolizja - pocisk gracza");
			break;
		case (3): // pocisk wroga
			print("kolizja - pocisk przeciwnika");
			break;
		case (4): // wróg
			print("kolizja - przeciwnik");
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

void Enemy::collide(PhysicalObject* coll)
{
	if (collider->intersects(*coll->collider))
	{
		switch (coll->collision_marker)
		{
		case (1): // gracz
			print("kolizja - gracz");
			break;
		case (2): // pocisk gracza
			print("kolizja - pocisk gracza");
			break;
		case (3): // pocisk wroga
			print("kolizja - pocisk przeciwnika");
			break;
		case (4): // wróg
			print("kolizja - przeciwnik");
			break;
		default:
			break;
		}
	}
}

Vector2f Enemy::handle_borders(Vector2f _pos)
{
	float _off0 = collider->width / 2.f - offset.x;
	float _off = collider->width / 2.f + offset.x;

	if (_pos.x - _off0 < 0)
	{
		_pos.x = _off0;
		direction.x = 1;
	}
	else if (_pos.x + _off > SCREEN_SIZE.x)
	{
		_pos.x = -_off + SCREEN_SIZE.x;
		direction.x = -1;
	}

	return _pos;
}

Projectile::Projectile(Vector2f pos, Sprite* s, Vector2i _frame, int _damage, float _rotation, float _spd_mod, int _coll_mask, int _dir) :
	PhysicalObject(pos, s, true, _frame), damage(_damage)
{
	collision_marker = _coll_mask;
	float proper_angle = _rotation / 57.3f;
	set_move(Vector2f(-_dir * sin(proper_angle), _dir * cos(proper_angle)), _spd_mod * base_velocity, 1.f, false);

	target_collision_mask = _coll_mask == 2 ? 4 : 1;
}

Projectile::~Projectile()
{
	print("PROJ: DTOR");
}

Vector2f Projectile::handle_borders(Vector2f _pos)
{
	if (-_pos.x > BULLET_BOUNDS_SIZE.x || -_pos.y > BULLET_BOUNDS_SIZE.y || _pos.x > SCREEN_SIZE.x + BULLET_BOUNDS_SIZE.x || _pos.y > SCREEN_SIZE.y + BULLET_BOUNDS_SIZE.y)
	{
		print("DEATH DEATH DEATH");
		
		destroy_this = true;
		//PhysicalObject::~PhysicalObject();
	}

	return _pos;
}

void Projectile::collide(PhysicalObject* coll)
{
	if (collider->intersects(*coll->collider))
	{
		if (coll->collision_marker == target_collision_mask)
		{
			static_cast<Character*>(coll)->take_hit(damage);

			delete this;
		}
	}
}
