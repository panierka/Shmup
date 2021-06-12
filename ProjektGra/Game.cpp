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
#pragma endregion


int main()
{
	print("start");

	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);
	MainMenu menu(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y);
	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::KeyReleased)
			{
				if (_event.key.code == Keyboard::PageDown)
				{
					menu.move_down();
				}
				if (_event.key.code == Keyboard::PageUp)
				{
					menu.move_up();
				}
				if (_event.key.code == Keyboard::Enter)
				{
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

					// inicjalizacja dodatkowych komponent�w
					InputHandler input(dynamic_cast<Player*>(Engine::objects[0].get()));
					Engine engine(&window);
					// inicjalizacja zmiennych do kalkulowania czasu mi�dzy klatkami
					Clock clock;
					float _frame_time = clock.getElapsedTime().asSeconds();

					//sound1.add_sound("pogchamp", "../Assets/Sounds/Soundtrack.wav", 20);

						//sound1.play_sound("pogchamp");
						/*BackgroundMusic background;*/
					WaveSpawner::big_enemies.push_back(spawn_fly);

					WaveSpawner::small_enemies.push_back(spawn_block1);
					WaveSpawner::small_enemies.push_back(spawn_block2);

					WaveSpawner wave;
					wave.set_wave(15);


					window.setFramerateLimit(60);
					// sprawdzenie zdarze� okna
					while (window.isOpen())
					{
						Event _event1;
						while (window.pollEvent(_event1))
						{
							if (_event1.type == Event::Closed)
							{
								window.close();
							}

						}
						// dynamiczne kalkulowanie realnego delta t mi�dzy kolejnymi klatkami z "wyg�adzaniem"
						_frame_time = clock.restart().asSeconds();


						wave.spawn(_frame_time);

						// sprawdzenie akcji gracza
						input.check_input();

						// wy�wietlanie poprawnych informacji na ekranie

						engine.update(_frame_time);

						// wykonanie si� oblicze� czasomierzy
						tick_timers(_frame_time);
					}
				}



			}
		}
		window.clear(Color(73, 84, 123, 255));
		menu.print_menu(window);
		window.display();
	}
	/*for (std::size_t i = 0; i < Engine::objects.size(); i++)
	{
		Engine::objects[i].reset();
	}*/

	print("");
	print("koniec");

	return EXIT_SUCCESS;
}