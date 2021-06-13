#include"Classes.h"
#include"KeyAction.h"
#include<iostream>
#include"WaveSpawner.h"

//Player& player = Player();

#pragma region > Przeciwnicy  < 

void spawn_fly()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(texture_atlas["fly"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 3, 12, *e, true));
	e->animations.push_back(new AnimationClip(4, 2, 10, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->set_move(Vector2f(1.f, -0.25f), 3.25f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{	
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle - 12.5f, 25.f, 2, 3, 8);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.85f;

	e->add_max_health(28);

	AttackTimer* at1 = new AttackTimer(1.f, *e);

	Engine::objects.push_back(std::move(e));
}

void spawn_fatman()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(texture_atlas["fat"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
	e->animations.push_back(new AnimationClip(2, 3, 12, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->set_move(Vector2f(1.f, -0.15f), 1.1f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle, 45, 8, 3, 8);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.5f;

	e->add_max_health(98);

	AttackTimer* at1 = new AttackTimer(3.f, *e);

	Engine::objects.push_back(std::move(e));
}

void spawn_block1()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(texture_atlas["block1"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 12, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 8, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->set_move(Vector2f(1.f, -0.35f), 1.75f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 12, 0, 0, 1, 3, 8);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.75f;

	e->add_max_health(21);

	AttackTimer* at1 = new AttackTimer(2.f, *e);

	Engine::objects.push_back(std::move(e));
}

void spawn_block2()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(texture_atlas["block2"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->set_move(Vector2f(1.f, -0.35f), 1.75f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		e.setHP(1);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.85f;

	e->add_max_health(36);

	AttackTimer* at1 = new AttackTimer(1.f, *e);

	Engine::objects.push_back(std::move(e));
}

void spawn_block3()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(texture_atlas["block3"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 8, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->set_move(Vector2f(1.f, -0.35f), 1.75f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 12, -15, 15, 3, 3, 8);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.75f;

	e->add_max_health(23);

	AttackTimer* at1 = new AttackTimer(4.f, *e);

	Engine::objects.push_back(std::move(e));
}

void spawn_block4()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(texture_atlas["block5"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 14, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->set_move(Vector2f(1.f, -0.35f), 1.75f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		if (magnitude(InputHandler::player->position - e.position) > 6.75f * ONE_UNIT_SIZE)
		{
			return;
		}

		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle , 0, 1, 3, 8);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.75f;

	e->add_max_health(23);

	AttackTimer* at1 = new AttackTimer(0.25f, *e);

	Engine::objects.push_back(std::move(e));
}
#pragma endregion


int main()
{
	print("start");

	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	MainMenu menu(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y);

	bool exit_menu = false;

	while (window.isOpen())
	{
		Event _event;

		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
			
			if (_event.type == Event::KeyReleased)
			{
				if (_event.key.code == Keyboard::Down)
				{
					menu.move_down();
				}
				if (_event.key.code == Keyboard::Up)
				{
					menu.move_up();
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 0)
				{
					exit_menu = true;
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 2)
				{
					window.close();
					//return 0;
				}
			}
		}

		if (exit_menu)
		{
			break;
		}

		window.clear(Color(73, 84, 123, 255));
		menu.print_menu(window);
		window.display();
	}

	// wczytanie tekstur gracza i stworzenie jego obiektu
	Texture t, t2;
	t.loadFromFile("../Assets/Player.png");
	t2.loadFromFile("../Assets/Player-Projectile.png");

#pragma region > Inicj. Tekstur <

	update_texture_atlas("player", "Player");
	update_texture_atlas("fly", "Fly");
	update_texture_atlas("player-bullet", "Player-Projectile");
	update_texture_atlas("enemy-bullet", "Enemy-Bullet");
	update_texture_atlas("player", "Player");
	update_texture_atlas("fly", "Fly");
	update_texture_atlas("player-bullet", "Player-Projectile");
	update_texture_atlas("enemy-bullet", "Enemy-Bullet");
	update_texture_atlas("block1", "Block1");
	update_texture_atlas("block2", "Block2");
	update_texture_atlas("block3", "Block3");
	update_texture_atlas("block5", "Block5");
	update_texture_atlas("player-bullet2", "player-bullet-2");
	update_texture_atlas("fat", "Fatman");

#pragma endregion


	std::unique_ptr<Player> _player = make_unique<Player>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 375), generate_sprite(texture_atlas["player"], Vector2f(50.f, 50.f)), false, Vector2i(100, 100));

	_player->animations.push_back(new AnimationClip(0, 4, 10, *_player, true));
	_player->animations.push_back(new AnimationClip(5, 4, 18, *_player, false));
	_player->animations.push_back(new AnimationClip(10, 3, 12, *_player, false));

	_player->create_collider(Vector2f(0.f, 14.f), Vector2f(36.f, 40.f));

	_player->add_max_health(60);
	_player->add_max_ammo(6);

	//_player->start();

	Engine::objects.push_back(std::move(_player));
	//player = *_player;

	Texture t1, t3;

	t1.loadFromFile("../Assets/Fly.png");
	t3.loadFromFile("../Assets/Enemy-Bullet.png");

	// inicjalizacja dodatkowych komponentów
	InputHandler input(dynamic_cast<Player*>(Engine::objects[0].get()));
	Engine engine(&window);
	// inicjalizacja zmiennych do kalkulowania czasu miêdzy klatkami
	Clock clock;
	float _frame_time = clock.getElapsedTime().asSeconds();

	//sound1.add_sound("pogchamp", "../Assets/Sounds/Soundtrack.wav", 20);

		//sound1.play_sound("pogchamp");
		/*BackgroundMusic background;*/
	WaveSpawner::big_enemies.push_back(spawn_fly);
	WaveSpawner::big_enemies.push_back(spawn_fatman);

	WaveSpawner::small_enemies.push_back(spawn_block1);
	WaveSpawner::small_enemies.push_back(spawn_block2);
	WaveSpawner::small_enemies.push_back(spawn_block3);
	WaveSpawner::small_enemies.push_back(spawn_block4);

	WaveSpawner wave;
	wave.set_wave(15);


	window.setFramerateLimit(60);
	// sprawdzenie zdarzeñ okna
	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
		}
		// dynamiczne kalkulowanie realnego delta t miêdzy kolejnymi klatkami z "wyg³adzaniem"
		_frame_time = clock.restart().asSeconds();


		wave.spawn(_frame_time);

		// sprawdzenie akcji gracza
		input.check_input();

		// wyœwietlanie poprawnych informacji na ekranie

		engine.update(_frame_time);

		// wykonanie siê obliczeñ czasomierzy
		tick_timers(_frame_time);
	}

	/*for (std::size_t i = 0; i < Engine::objects.size(); i++)
	{
		Engine::objects[i].reset();
	}*/

	print("");
	print("koniec");

	return EXIT_SUCCESS;
}