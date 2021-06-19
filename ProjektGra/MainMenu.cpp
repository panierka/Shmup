#include "MainMenu.h"
Vector2f enemy_spawn_pos = (Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, -450);
SetVolume setVolume;

#pragma region > Przeciwnicy  < 

float Game::random_dir()
{
	return random_number(0, 1) ? 1.f : -1.f;
}

void Game::spawn_fly()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["fly"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 3, 12, *e, true));
	e->animations.push_back(new AnimationClip(4, 2, 10, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	
	e->score_value = 500;

	e->set_move(Vector2f(1.f * random_dir(), -0.25f), 3.25f, 1, true);

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

void Game::spawn_fatman()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["fat"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
	e->animations.push_back(new AnimationClip(2, 3, 12, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 500;
	e->set_move(Vector2f(1.f * random_dir(), -0.15f), 1.1f, 1, true);

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

void Game::spawn_block1()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["block1"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 12, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 8, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 250;
	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

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

void Game::spawn_block2()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["block2"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 250;
	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

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

void Game::spawn_block3()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["block3"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 8, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 250;
	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

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

void Game::spawn_block4()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["block5"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 10, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 14, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 250;
	e->set_move(Vector2f(1.f * random_dir(), -0.35f), 1.75f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		if (magnitude(InputHandler::player->position - e.position) > 5.75f * ONE_UNIT_SIZE)
		{
			return;
		}

		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle, 0, 1, 3, 8);
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.75f;

	e->add_max_health(23);

	AttackTimer* at1 = new AttackTimer(0.25f, *e);

	Engine::objects.push_back(std::move(e));
}

void Game::spawn_priest()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["priest"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 3, 8, *e, true));
	e->animations.push_back(new AnimationClip(4, 3, 8, *e, false));
	e->animations.push_back(new AnimationClip(7, 3, 8, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 500;
	e->set_move(Vector2f(1.f * random_dir(), -0.175f), 1.05f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 12, -33, 11, 6, 3, 8);
	};

	void (*f1)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(2);
		spawn_block1();
	};

	e->attacks.push_back(f);
	e->attacks.push_back(f1);

	e->bullet_velocity_mod = 0.55f;

	e->add_max_health(32);

	AttackTimer* at1 = new AttackTimer(9.f, *e);

	Engine::objects.push_back(std::move(e));
}

void Game::spawn_prince()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["prince"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
	e->animations.push_back(new AnimationClip(2, 2, 10, *e, false));
	e->animations.push_back(new AnimationClip(5, 2, 10, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 500;
	e->set_move(Vector2f(1.f * random_dir(), -0.225f), 2.5f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 12, -45, 90, 4, 3, 8);
	};

	void (*f1)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(2);
		e.shoot("enemy-bullet", Vector2i(25, 25), 12, 0, 90, 4, 3, 8);
	};

	e->attacks.push_back(f);
	e->attacks.push_back(f1);

	e->bullet_velocity_mod = 1.05f;

	e->add_max_health(32);

	AttackTimer* at1 = new AttackTimer(1.5f, *e);

	Engine::objects.push_back(std::move(e));
}

void Game::spawn_sniper()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos, generate_sprite(TextureAtlas::texture_atlas["sniper"], Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 3, 10, *e, true));
	e->animations.push_back(new AnimationClip(4, 2, 10, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));
	e->score_value = 500;
	e->set_move(Vector2f(1.f * random_dir(), -0.125f), 1.15f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("saw", Vector2i(50, 50), 58, angle, 0, 1, 3, 8);
	};

	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.95f;

	e->add_max_health(18);

	AttackTimer* at1 = new AttackTimer(1.5f, *e);

	Engine::objects.push_back(std::move(e));
}

void Game::spawn_boss()
{
	std::unique_ptr<Enemy> e = make_unique <Enemy>(enemy_spawn_pos + Vector2f(0, 150), generate_sprite(TextureAtlas::texture_atlas["BOSS"], Vector2f(100.f, 100.f)), true, Vector2i(200, 200));

	e->animations.push_back(new AnimationClip(0, 2, 8, *e, true));
	e->animations.push_back(new AnimationClip(3, 2, 10, *e, false));
	e->animations.push_back(new AnimationClip(6, 2, 10, *e, false));
	e->animations.push_back(new AnimationClip(9, 2, 10, *e, false));
	e->animations.push_back(new AnimationClip(11, 2, 10, *e, false));

	e->create_collider(Vector2f(-50.f, -50.f), Vector2f(150.f, 150.f));
	e->score_value = 60000;
	e->set_move(Vector2f(1.f, 0.f), 2.0f, 1, true);

	void (*f1)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.bullet_velocity_mod = 1.f;
		e.shoot("enemy-bullet", Vector2i(25, 25), 18, -25.f, 12.5f, 5, 3, 8);
		e.shoot("saw", Vector2i(50, 50), 59, angle, 0, 1, 3, 8);
	};

	void (*f2)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(2);
		e.bullet_velocity_mod = 0.8f;
		e.shoot("enemy-bullet", Vector2i(25, 25), 16, 0, 30.f, 12, 3, 8);
	};

	void (*f3)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(3);
		e.bullet_velocity_mod = 1.2f;
		e.shoot("enemy-bullet", Vector2i(25, 25), 32, angle - 2.5f, 5.f, 2, 3, 8);
	};

	void (*f4)(Enemy&) = [](Enemy& e)
	{
		if (random_number(0, 3) == 0)
		{
			e.call_animation(4);
			spawn_block1();
		}
	};

	e->attacks.push_back(f1);
	e->attacks.push_back(f2);
	e->attacks.push_back(f3);
	e->attacks.push_back(f4);

	e->add_max_health(1600);

	AttackTimer* at1 = new AttackTimer(0.85f, *e);

	Engine::objects.push_back(std::move(e));
}

#pragma endregion

Menu::Menu()
{
	font = new Font();
	font->loadFromFile("../Assets/arial.ttf");
	text[0].setFont(*font);
	text[0].setString("Play");
	text[0].setPosition(Vector2f(400u, 200u));
	text[1].setFont(*font);
	text[1].setString("Sound Volume");
	text[1].setPosition(Vector2f(400u, 300u));
	text[2].setFont(*font);
	text[2].setString("Music Volume");
	text[2].setPosition(Vector2f(400u, 400u));
	text[3].setFont(*font);
	text[3].setString("General Volume");
	text[3].setPosition(Vector2f(400u, 500u));
	text[4].setFont(*font);
	text[4].setString("Leaderboard");
	text[4].setPosition(Vector2f(400u, 600u));
	text[5].setFont(*font);
	text[5].setString("Exit");
	text[5].setPosition(Vector2f(400u, 700u));
	current_position = 0;
	text[current_position].setFillColor(Color::Red);
	text1[0].setFont(*font);
	text1[0].setPosition(Vector2f(200u, 800u));
	text1[2].setFont(*font);
	text1[2].setPosition(Vector2f(800u, 800u));
	text1[1].setFont(*font);
	text1[1].setPosition(Vector2f(400u, 800u));
	current_position2 = 2;
	text1[current_position2].setFillColor(Color::Red);
}

Menu::~Menu()
{
	delete font;
}

string Menu::print_string(int volume)
{
	string circles{};
	string number{};
	for (int i = 0; i < volume; i++)
	{
		circles += "O";
	}
	for (int j = 0; j < 10 - volume; j++)
	{
		circles += "X";
	}
	number = to_string(volume * 10);
	return circles + "	" + number;
}
void Menu::print_menu(RenderWindow& window)
{
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
	{
		window.draw(text[i]);
	}
}

void Menu::move_up()
{
	if (current_position > 0)
	{
		text[current_position].setFillColor(Color::White);
		current_position--;
		text[current_position].setFillColor(Color::Red);
	}
	else if (current_position == 0)
	{
		text[0].setFillColor(Color::White);
		current_position = NUMBER_OF_ELEMENTS - 1;
		text[current_position].setFillColor(Color::Red);
	}
}

void Menu::move_down()
{
	if (current_position + 1 < NUMBER_OF_ELEMENTS)
	{
		text[current_position].setFillColor(Color::White);
		current_position++;
		text[current_position].setFillColor(Color::Red);
	}
	else if (current_position == NUMBER_OF_ELEMENTS - 1)
	{
		text[NUMBER_OF_ELEMENTS - 1].setFillColor(Color::White);
		current_position = 0;
		text[current_position].setFillColor(Color::Red);
	}
}

void Menu::move_right_to_volume()
{
	text1[current_position2].setFillColor(Color::White);
	if (current_position2 == 2)
		current_position2 = -1;
	current_position2++;
	if (current_position2 == 1)
		current_position2++;
	text1[current_position2].setFillColor(Color::Red);
}

void Menu::move_left_to_volume()
{
	text1[current_position2].setFillColor(Color::White);
	if (current_position2 == 0)
		current_position2 = 3;
	current_position2--;
	if (current_position2 == 1)
		current_position2--;
	text1[current_position2].setFillColor(Color::Red);
}

int MainMenu::Run(RenderWindow& window)
{
	Menu menu;
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
				menu.text1[0].setString("Down");
				menu.text1[2].setString("Up");
				if (_event.key.code == Keyboard::Down)
				{
					show_volume_interface = false;
					menu.move_down();
				}
				if (_event.key.code == Keyboard::Up)
				{
					show_volume_interface = false;
					menu.move_up();
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 0)
				{
					return 1;
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 1)
				{
					show_volume_interface = true;
					menu.text1[1].setString(menu.print_string(sound_volume));
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 2)
				{
					show_volume_interface = true;
					menu.text1[1].setString(menu.print_string(music_volume));
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 3)
				{
					show_volume_interface = true;
					menu.text1[1].setString(menu.print_string(general_volume));
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 4)
				{
					//leaderboard
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 5)
				{
					//window.close();
					return -1;
				}
				if (show_volume_interface)
				{
						if (_event.key.code == Keyboard::Left)
						{
							menu.move_left_to_volume();
						}
						if (_event.key.code == Keyboard::Right)
						{
							menu.move_right_to_volume();
						}
						if (_event.key.code == Keyboard::Space && menu.current_position2 == 2)
						{
							switch (menu.current_position)
							{
							case (1):
								setVolume.turn_up(sound_volume);
								menu.text1[1].setString(menu.print_string(sound_volume));
								break;
							case (2):
								setVolume.turn_up(music_volume);
								menu.text1[1].setString(menu.print_string(music_volume));
								break;
							case (3):
								setVolume.turn_up(general_volume);
								menu.text1[1].setString(menu.print_string(general_volume));
								break;
							}
							/*sound1.play_sound("pogchamp1");*/	//nie dzia³a, bo dŸwiêk wczytywany dopiero przy pierwszej rozgrywce
						}
						if (_event.key.code == Keyboard::Space && menu.current_position2 == 0)
						{
							switch (menu.current_position)
							{
							case (1):
								setVolume.turn_down(sound_volume);
								menu.text1[1].setString(menu.print_string(sound_volume));
								break;
							case (2):
								setVolume.turn_down(music_volume);
								menu.text1[1].setString(menu.print_string(music_volume));
								break;
							case (3):
								setVolume.turn_down(general_volume);
								menu.text1[1].setString(menu.print_string(general_volume));
								break;
							}
						}
				}
			}
		}
		window.clear(Color(73, 84, 123, 255));
		menu.print_menu(window);
		if (show_volume_interface)
		{
			for (int i = 0; i < 3; i++)
			{
				window.draw(menu.text1[i]);
			}
		}
		window.display();
	}
}

int Game::Run(RenderWindow& window)
{
	Engine::objects.clear();
	Engine::stat_upgrades.clear();

	DisplayHP display;

	// wczytanie tekstur gracza i stworzenie jego obiektu
	Texture t, t2;
	t.loadFromFile("../Assets/Player.png");
	t2.loadFromFile("../Assets/Player-Projectile.png");

	std::unique_ptr<Player> _player = make_unique<Player>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 425), generate_sprite(TextureAtlas::texture_atlas["player"], Vector2f(50.f, 50.f)), false, Vector2i(100, 100));

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

	sound1.add_sound("pogchamp", "../Assets/Sounds/Soundtrack.wav", 20);
	sound1.add_sound("pogchamp1", "../Assets/Sounds/plantLoud.wav", 100);
	/*sound1.play_sound("pogchamp");*/
	sound1.play_sound("pogchamp1");
		/*BackgroundMusic background;*/

	PauseMenu pause_menu;

	waves = WaveSpawner();
	waves.next_wave();

	window.setFramerateLimit(60);
	bool pause_game = false;
	int pause_action_index = 0;

	game_state = 0;

	// sprawdzenie zdarzeñ okna
	while (window.isOpen())
	{
		Event _event;

		pause_action_index = 0;

		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
			else if (_event.type == Event::KeyReleased)
			{
				pause_menu.text1[0].setString("Down");
				pause_menu.text1[2].setString("Up");
				if (_event.key.code == Keyboard::Escape)
				{
					pause_game = true;
				}
				if (_event.key.code == Keyboard::Down)
				{
					show_volume_interface = false;
					pause_action_index = 2;
				}
				if (_event.key.code == Keyboard::Up)
				{
					show_volume_interface = false;
					pause_action_index = 3;
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 0)
				{
					pause_action_index = 4;
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 1)
				{
					return 2;
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 2)
				{
					show_volume_interface = true;
					pause_menu.text1[1].setString(pause_menu.print_string(sound_volume));
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 3)
				{
					show_volume_interface = true;
					pause_menu.text1[1].setString(pause_menu.print_string(music_volume));
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 4)
				{
					show_volume_interface = true;
					pause_menu.text1[1].setString(pause_menu.print_string(general_volume));
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 5)
				{
					return 0;
				}
				if (show_volume_interface)
				{
					if (_event.key.code == Keyboard::Left)
					{
						pause_menu.move_left_to_volume();
					}
					if (_event.key.code == Keyboard::Right)
					{
						pause_menu.move_right_to_volume();
					}
					if (_event.key.code == Keyboard::Space && pause_menu.current_position2 == 2)
					{
						switch (pause_menu.current_position)
						{
						case (2):
							setVolume.turn_up(sound_volume);
							pause_menu.text1[1].setString(pause_menu.print_string(sound_volume));
							break;
						case (3):
							setVolume.turn_up(music_volume);
							pause_menu.text1[1].setString(pause_menu.print_string(music_volume));
							break;
						case (4):
							setVolume.turn_up(general_volume);
							pause_menu.text1[1].setString(pause_menu.print_string(general_volume));
							break;
						}
						/*sound1.play_sound("pogchamp1");*/	//nie dzia³a, bo dŸwiêk wczytywany dopiero przy pierwszej rozgrywce
					}
					if (_event.key.code == Keyboard::Space && pause_menu.current_position2 == 0)
					{
						switch (pause_menu.current_position)
						{
						case (2):
							setVolume.turn_down(sound_volume);
							pause_menu.text1[1].setString(pause_menu.print_string(sound_volume));
							break;
						case (3):
							setVolume.turn_down(music_volume);
							pause_menu.text1[1].setString(pause_menu.print_string(music_volume));
							break;
						case (4):
							setVolume.turn_down(general_volume);
							pause_menu.text1[1].setString(pause_menu.print_string(general_volume));
							break;
						}
					}
				}
			}
		}

		if (!pause_game)
		{
			// dynamiczne kalkulowanie realnego delta t miêdzy kolejnymi klatkami z "wyg³adzaniem"
			_frame_time = clock.restart().asSeconds();

			waves.spawn(_frame_time);

			// sprawdzenie akcji gracza
			input.check_input();

			// wyœwietlanie poprawnych informacji na ekranie

			engine.update(_frame_time);

			// wykonanie siê obliczeñ czasomierzy
			tick_timers(_frame_time);

			if (game_state == 1)
			{
				return 3;
			}
			else if (game_state == 2)
			{
				return 4;
			}
		}
		else
		{
			clock.restart();
			_frame_time = 0;

			switch (pause_action_index)
			{
			case 2:
				pause_menu.move_down();
				break;
			case 3:
				pause_menu.move_up();
				break;
			case 4:
				pause_game = false;
				break;
			default:
				break;
			}



			/*if(Keyboard::isKeyPressed(Keyboard::Down))
			{
				pause_menu.move_down();
			}
			*/

			window.clear(Color(73, 84, 123, 255));
			pause_menu.print_menu(window);
			if (show_volume_interface)
			{
				for (int i = 0; i < 3; i++)
				{
					window.draw(pause_menu.text1[i]);
				}
			}
			window.display();

		}
	}

	/*for (std::size_t i = 0; i < Engine::objects.size(); i++)
	{
		Engine::objects[i].reset();
	}*/

	return -1; //EXIT_SUCCESS;
}


PauseMenu::PauseMenu() :Menu()
{
	font1 = new Font();
	font1->loadFromFile("../Assets/arial.ttf");
	text[0].setFont(*font1);
	text[0].setString("Resume");
	text[0].setPosition(Vector2f(400u, 200u));
	text[1].setFont(*font1);
	text[1].setString("Restart");
	text[1].setPosition(Vector2f(400u, 300u));
	text[2].setFont(*font1);
	text[2].setString("Sound Volume");
	text[2].setPosition(Vector2f(400u, 400u));
	text[3].setFont(*font1);
	text[3].setString("Music Volume");
	text[3].setPosition(Vector2f(400u, 500u));
	text[4].setFont(*font1);
	text[4].setString("General Volume");
	text[4].setPosition(Vector2f(400u, 600u));
	text[5].setFont(*font1);
	text[5].setString("Exit");
	text[5].setPosition(Vector2f(400u, 700u));
	current_position = 0;
	text[current_position].setFillColor(Color::Red);
}

PauseMenu::~PauseMenu()
{
	delete font1;
}
MainMenu::MainMenu()
{

}
MainMenu::~MainMenu()
{

}
Game::Game()
{
	WaveSpawner::boss = spawn_boss;

	WaveSpawner::big_enemies.push_back(spawn_fly);
	WaveSpawner::big_enemies.push_back(spawn_fatman);
	WaveSpawner::big_enemies.push_back(spawn_priest);
	WaveSpawner::big_enemies.push_back(spawn_prince);
	WaveSpawner::big_enemies.push_back(spawn_sniper);

	WaveSpawner::small_enemies.push_back(spawn_block1);
	WaveSpawner::small_enemies.push_back(spawn_block2);
	WaveSpawner::small_enemies.push_back(spawn_block3);
	WaveSpawner::small_enemies.push_back(spawn_block4);
}
Game::~Game()
{

}
//int PauseMenu::Run(RenderWindow& window)
//{
//
//}

//int Menu::Run(RenderWindow& window)
//{
//
//}

//MainMenu::MainMenu()
//{
//
//}
//
//MainMenu::MainMenu(int screen_size_x, int screen_size_y)
//{
//	font = new Font();
//	font->loadFromFile("../Assets/arial.ttf");
//	text[0].setFont(*font);
//	text[0].setString("Play");
//	text[0].setPosition(Vector2f(400u, 350u));
//	text[1].setFont(*font);
//	text[1].setString("Leaderboard");
//	text[1].setPosition(Vector2f(400u, 450u));
//	text[2].setFont(*font);
//	text[2].setString("Exit");
//	text[2].setPosition(Vector2f(400u, 550u));
//	current_position = 0;
//	text[current_position].setFillColor(Color::Red);
//}
//
//MainMenu::~MainMenu()
//{
//	delete font;
//}
//
//void MainMenu::print_menu(RenderWindow& window)
//{
//	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
//	{
//		window.draw(text[i]);
//	}
//}
//
//void MainMenu::move_up()
//{
//	if (current_position  > 0)
//	{
//		text[current_position].setFillColor(Color::White);
//		current_position--;
//		text[current_position].setFillColor(Color::Red);
//	}
//}
//
//void MainMenu::move_down()
//{
//	if (current_position + 1 < NUMBER_OF_ELEMENTS)
//	{
//		text[current_position].setFillColor(Color::White);
//		current_position++;
//		text[current_position].setFillColor(Color::Red);
//	}
//}

//PauseMenu::PauseMenu(int screen_size_x, int screen_size_y):MainMenu()
//{
//	font1 = new Font();
//	font1->loadFromFile("../Assets/arial.ttf");
//	text[0].setFont(*font1);
//	text[0].setString("Resume");
//	text[0].setPosition(Vector2f(400u, 350u));
//	text[1].setFont(*font1);
//	text[1].setString("Restart");
//	text[1].setPosition(Vector2f(400u, 450u));
//	text[2].setFont(*font1);
//	text[2].setString("Exit");
//	text[2].setPosition(Vector2f(400u, 550u));
//	current_position = 0;
//	text[current_position].setFillColor(Color::Red);
//}
//
//PauseMenu::~PauseMenu()
//{
//	delete font1;
//}

Restart::Restart()
{

}

Restart::~Restart()
{

}

int Restart::Run(RenderWindow& window)
{
	return 1;
}

EndScreen::EndScreen(string _screen_key) :
	screen_key(_screen_key)
{
	
}

EndScreen::~EndScreen()
{

}

int EndScreen::Run(RenderWindow& window)
{
	Sprite endScreen;
	endScreen.setTexture(*TextureAtlas::texture_atlas[screen_key]);

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
				if (_event.key.code == Keyboard::Escape)
				{
					return 0;
				}
				else if (_event.key.code == Keyboard::R)
				{
					return 2;
				}
			}
		}
		
		window.clear();
		window.draw(endScreen);
		window.display();
	}

	return -1;
}
