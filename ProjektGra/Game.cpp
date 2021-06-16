#include "MainMenu.h"
#include"Classes.h"
#include"KeyAction.h"
#include<iostream>
#include<cstdlib>

//Player& player = Player();

WaveSpawner waves{};

//Vector2f enemy_spawn_pos = (Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, -450);

//#pragma region > Przeciwnicy  < 

//float random_dir()
//{
//	return random_number(0, 1) ? 1.f : -1.f;
//}

//void spawn_fly()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["fly"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 3, 12, *e, true));
//	e->animations.push_back(new AnimationClip(4, 2, 10, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.25f), 3.25f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{	
//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle - 12.5f, 25.f, 2, 3, 8);
//	};
//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.85f;

//	e->add_max_health(28);

//	AttackTimer* at1 = new AttackTimer(1.f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_fatman()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["fat"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
//	e->animations.push_back(new AnimationClip(2, 3, 12, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.15f), 1.1f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle, 45, 8, 3, 8);
//	};
//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.5f;

//	e->add_max_health(98);

//	AttackTimer* at1 = new AttackTimer(3.f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_block1()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["block1"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 2, 12, *e, true));
//	e->animations.push_back(new AnimationClip(2, 2, 8, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 12, 0, 0, 1, 3, 8);
//	};
//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.75f;

//	e->add_max_health(21);

//	AttackTimer* at1 = new AttackTimer(2.f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_block2()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["block2"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		e.setHP(1);
//	};
//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.85f;

//	e->add_max_health(36);

//	AttackTimer* at1 = new AttackTimer(1.f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_block3()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["block3"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));
//	e->animations.push_back(new AnimationClip(2, 2, 8, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 12, -15, 15, 3, 3, 8);
//	};
//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.75f;

//	e->add_max_health(23);

//	AttackTimer* at1 = new AttackTimer(4.f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_block4()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["block5"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));
//	e->animations.push_back(new AnimationClip(2, 2, 14, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		if (magnitude(InputHandler::player->position - e.position) > 5.75f * ONE_UNIT_SIZE)
//		{
//			return;
//		}

//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle , 0, 1, 3, 8);
//	};
//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.75f;

//	e->add_max_health(23);

//	AttackTimer* at1 = new AttackTimer(0.25f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_priest()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["priest"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 3, 8, *e, true));
//	e->animations.push_back(new AnimationClip(4, 3, 8, *e, false));
//	e->animations.push_back(new AnimationClip(7, 3, 8, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.175f), 1.05f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 12, -33, 11, 6, 3, 8);
//	};

//	void (*f1)(Enemy&) = [](Enemy& e)
//	{
//		e.call_animation(2);
//		spawn_block1();
//	};

//	e->attacks.push_back(f);
//	e->attacks.push_back(f1);

//	e->bullet_velocity_mod = 0.55f;

//	e->add_max_health(32);

//	AttackTimer* at1 = new AttackTimer(9.f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_prince()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["prince"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
//	e->animations.push_back(new AnimationClip(2, 2, 10, *e, false));
//	e->animations.push_back(new AnimationClip(5, 2, 10, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.225f), 2.5f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		e.call_animation(1);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 12, -45, 90, 4, 3, 8);
//	};

//	void (*f1)(Enemy&) = [](Enemy& e)
//	{
//		e.call_animation(2);
//		e.shoot("enemy-bullet", Vector2i(25, 25), 12, 0, 90, 4, 3, 8);
//	};

//	e->attacks.push_back(f);
//	e->attacks.push_back(f1);

//	e->bullet_velocity_mod = 1.05f;

//	e->add_max_health(32);

//	AttackTimer* at1 = new AttackTimer(1.5f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_sniper()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(texture_atlas["sniper"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

//	e->animations.push_back(new AnimationClip(0, 3, 10, *e, true));
//	e->animations.push_back(new AnimationClip(4, 2, 10, *e, false));

//	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

//	e->set_move(Vector2f(1.f * random_dir(), -0.125f), 1.15f, 1, true);

//	void (*f)(Enemy&) = [](Enemy& e)
//	{
//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.shoot("saw", Vector2i(50, 50), 58, angle, 0, 1, 3, 8);
//	};

//	e->attacks.push_back(f);

//	e->bullet_velocity_mod = 0.95f;

//	e->add_max_health(18);

//	AttackTimer* at1 = new AttackTimer(1.5f, *e);

//	Engine::objects.push_back(std::move(e));
//}

//void spawn_boss()
//{
//	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos + Vector2f(0, 150), generate_sprite(texture_atlas["BOSS"], Vector2f(100.f, 100.f)), true, Vector2i(200, 200));

//	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
//	e->animations.push_back(new AnimationClip(3, 2, 10, *e, false));
//	e->animations.push_back(new AnimationClip(6, 2, 10, *e, false));
//	e->animations.push_back(new AnimationClip(9, 2, 10, *e, false));
//	e->animations.push_back(new AnimationClip(11, 2, 10, *e, false));

//	e->create_collider(Vector2f(-50.f, -50.f), Vector2f(150.f, 150.f));

//	e->set_move(Vector2f(1.f, 0.f), 2.0f, 1, true);

//	void (*f1)(Enemy&) = [](Enemy& e)
//	{
//		float angle = e.angle_to_player();
//		e.call_animation(1);
//		e.bullet_velocity_mod = 1.f;
//		e.shoot("enemy-bullet", Vector2i(25, 25), 18, -25.f, 12.5f, 5, 3, 8);
//		e.shoot("saw", Vector2i(50, 50), 59, angle, 0, 1, 3, 8);
//	};

//	void (*f2)(Enemy&) = [](Enemy& e)
//	{
//		e.call_animation(2);
//		e.bullet_velocity_mod = 0.8f;
//		e.shoot("enemy-bullet", Vector2i(25, 25), 16, 0, 30.f, 12, 3, 8);
//	};

//	void (*f3)(Enemy&) = [](Enemy& e)
//	{
//		float angle = e.angle_to_player();
//		e.call_animation(3);
//		e.bullet_velocity_mod = 1.2f;
//		e.shoot("enemy-bullet", Vector2i(25, 25), 32, angle - 2.5f, 5.f, 2, 3, 8);
//	};

//	void (*f4)(Enemy&) = [](Enemy& e)
//	{
//		if (random_number(0, 3) == 0)
//		{
//			e.call_animation(4);
//			spawn_block1();
//		}
//	};

//	e->attacks.push_back(f1);
//	e->attacks.push_back(f2);
//	e->attacks.push_back(f3);
//	e->attacks.push_back(f4);

//	e->add_max_health(1600);

//	AttackTimer* at1 = new AttackTimer(0.85f, *e);

//	Engine::objects.push_back(std::move(e));
//}

#pragma endregion


int main()
{
	vector<cScreen*>Screens;
	int screen = 0;
	print("start");
	srand(time(0));
	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	MainMenu main_menu;
	Screens.push_back(&main_menu); // 0
	Game game;
	Screens.push_back(&game); // 1
	Restart restart;
	Screens.push_back(&restart); // 2

	/*Screens.erase(Screens.begin());*/

	while (screen >= 0)
	{
		//if (counter > 0)							//za ka¿dym razem (poza pierwszym)
		//{
		//	Screens.erase(Screens.begin() + 1);		//usuwamy z wektora obiekt gry
		//	Game game;								
		//	Screens.push_back(&game);				//dopisujemy now¹ na koñcu
		//}											//ale nie dzia³a
		screen = Screens[screen]->Run(window);
	}

	return EXIT_SUCCESS;
}


//int main()
//{
//	print("start");
//
//	srand(time(0));
//
//	// stworzenie okna gry
//	RenderWindow window(VideoMode(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);
//
//	Menu menu;
//	PauseMenu pause_menu;
//	bool exit_menu = false;
//
//	while (window.isOpen())
//	{
//		Event _event;
//
//		while (window.pollEvent(_event))
//		{
//			if (_event.type == Event::Closed)
//			{
//				window.close();
//			}
//			
//			if (_event.type == Event::KeyReleased)
//			{
//				if (_event.key.code == Keyboard::Down)
//				{
//					menu.move_down();
//				}
//				if (_event.key.code == Keyboard::Up)
//				{
//					menu.move_up();
//				}
//				if (_event.key.code == Keyboard::Enter && menu.current_position == 0)
//				{
//					exit_menu = true;
//				}
//				if (_event.key.code == Keyboard::Enter && menu.current_position == 2)
//				{
//					window.close();
//					//return 0;
//				}
//			}
//		}
//
//		if (exit_menu)
//		{
//			break;
//		}
//
//		window.clear(Color(73, 84, 123, 255));
//		menu.print_menu(window);
//		window.display();
//	}
//
//	// wczytanie tekstur gracza i stworzenie jego obiektu
//	Texture t, t2;
//	t.loadFromFile("../Assets/Player.png");
//	t2.loadFromFile("../Assets/Player-Projectile.png");
//
//#pragma region > Inicj. Tekstur <
//
//	update_texture_atlas("player", "Player");
//	update_texture_atlas("fly", "Fly");
//	update_texture_atlas("player-bullet", "Player-Projectile");
//	update_texture_atlas("enemy-bullet", "Enemy-Bullet");
//	update_texture_atlas("player", "Player");
//	update_texture_atlas("fly", "Fly");
//	update_texture_atlas("player-bullet", "Player-Projectile");
//	update_texture_atlas("enemy-bullet", "Enemy-Bullet");
//	update_texture_atlas("block1", "Block1");
//	update_texture_atlas("block2", "Block2");
//	update_texture_atlas("block3", "Block3");
//	update_texture_atlas("block5", "Block5");
//	update_texture_atlas("player-bullet2", "player-bullet-2");
//	update_texture_atlas("fat", "Fatman");
//	update_texture_atlas("priest", "Priest");
//	update_texture_atlas("saw", "saw");
//	update_texture_atlas("prince", "Prince");
//	update_texture_atlas("sniper", "Sniper");
//	update_texture_atlas("bck", "Background");
//	update_texture_atlas("line", "Stat_Line");
//	update_texture_atlas("stats", "Stats");
//	update_texture_atlas("BOSS", "Boss");
//
//#pragma endregion
//
//
//	std::unique_ptr<Player> _player = make_unique<Player>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 425), generate_sprite(texture_atlas["player"], Vector2f(50.f, 50.f)), false, Vector2i(100, 100));
//
//	_player->animations.push_back(new AnimationClip(0, 4, 10, *_player, true));
//	_player->animations.push_back(new AnimationClip(5, 4, 18, *_player, false));
//	_player->animations.push_back(new AnimationClip(10, 3, 12, *_player, false));
//
//	_player->create_collider(Vector2f(0.f, 14.f), Vector2f(36.f, 40.f));
//
//	_player->add_max_health(60);
//	_player->add_max_ammo(6);
//
//	//_player->start();
//
//	Engine::objects.push_back(std::move(_player));
//	//player = *_player;
//
//	Texture t1, t3;
//
//	t1.loadFromFile("../Assets/Fly.png");
//	t3.loadFromFile("../Assets/Enemy-Bullet.png");
//
//	// inicjalizacja dodatkowych komponentów
//	InputHandler input(dynamic_cast<Player*>(Engine::objects[0].get()));
//	Engine engine(&window);
//	// inicjalizacja zmiennych do kalkulowania czasu miêdzy klatkami
//	Clock clock;
//	float _frame_time = clock.getElapsedTime().asSeconds();
//
//	//sound1.add_sound("pogchamp", "../Assets/Sounds/Soundtrack.wav", 20);
//
//		//sound1.play_sound("pogchamp");
//		/*BackgroundMusic background;*/
//
//	WaveSpawner::boss = Game::spawn_boss;
//
//	WaveSpawner::big_enemies.push_back(Game::spawn_fly);
//	WaveSpawner::big_enemies.push_back(Game::spawn_fatman);
//	WaveSpawner::big_enemies.push_back(Game::spawn_priest);
//	WaveSpawner::big_enemies.push_back(Game::spawn_prince);
//	WaveSpawner::big_enemies.push_back(Game::spawn_sniper);
//
//	WaveSpawner::small_enemies.push_back(Game::spawn_block1);
//	WaveSpawner::small_enemies.push_back(Game::spawn_block2);
//	WaveSpawner::small_enemies.push_back(Game::spawn_block3);
//	WaveSpawner::small_enemies.push_back(Game::spawn_block4);
//
//	/*WaveSpawner wave;
//	wave.next_wave();*/
//
//
//	waves = WaveSpawner();
//	waves.next_wave();
//
//	window.setFramerateLimit(60);
//	bool pause_game = false;
//
//	int pause_action_index = 0;
//
//	// sprawdzenie zdarzeñ okna
//	while (window.isOpen())
//	{
//		Event _event;
//
//		pause_action_index = 0;
//
//		while (window.pollEvent(_event))
//		{
//			if (_event.type == Event::Closed)
//			{
//				window.close();
//			}
//			else if (_event.type == Event::KeyReleased)
//			{
//				if (_event.key.code == Keyboard::Escape)
//				{
//					pause_game = true;
//				}
//				if (_event.key.code == Keyboard::Down)
//				{
//					pause_action_index = 2;
//				}
//				if (_event.key.code == Keyboard::Up)
//				{
//					pause_action_index = 3;
//				}
//				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 0)
//				{
//					pause_action_index = 4;
//					break;
//				}
//				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 2)
//				{
//					pause_action_index = 5;
//					//return 0;
//				}
//			}
//		}
//		
//		if (!pause_game)
//		{
//			// dynamiczne kalkulowanie realnego delta t miêdzy kolejnymi klatkami z "wyg³adzaniem"
//			_frame_time = clock.restart().asSeconds();
//
//			waves.spawn(_frame_time);
//
//			// sprawdzenie akcji gracza
//			input.check_input();
//
//			// wyœwietlanie poprawnych informacji na ekranie
//
//			engine.update(_frame_time);
//
//			// wykonanie siê obliczeñ czasomierzy
//			tick_timers(_frame_time);
//		}
//		else
//		{
//			clock.restart();
//			_frame_time = 0;
//
//			switch (pause_action_index)
//			{
//			case 2:
//				pause_menu.move_down();
//				break;
//			case 3:
//				pause_menu.move_up();
//				break;
//			case 4:
//				pause_game = false;
//				break;
//			case 5:
//				window.close();
//				break;
//			default:
//				break;
//			}
//			
//			
//			
//			/*if(Keyboard::isKeyPressed(Keyboard::Down))
//			{
//				pause_menu.move_down();
//			}
//			*/
//
//			window.clear(Color(73, 84, 123, 255));
//			pause_menu.print_menu(window);
//			window.display();
//			
//		}
//	}
//
//	/*for (std::size_t i = 0; i < Engine::objects.size(); i++)
//	{
//		Engine::objects[i].reset();
//	}*/
//
//	print("");
//	print("koniec");
//
//	return EXIT_SUCCESS;
//}