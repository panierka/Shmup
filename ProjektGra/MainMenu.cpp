#include "MainMenu.h"
Vector2f enemy_spawn_pos = (Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, -450);
SetVolume setVolume;

bool escape = true;
bool no_data = true;
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
		sound1.play_sound("buzzing");
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

	e->create_collider(Vector2f(-5.f, 0.f), Vector2f(60.f, 50.f));
	e->score_value = 500;
	e->set_move(Vector2f(1.f * random_dir(), -0.15f), 1.1f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot("enemy-bullet", Vector2i(25, 25), 10, angle, 45, 8, 3, 8);
		sound1.play_sound("fat");
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
		sound1.play_sound("small_enemy_shot");
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
		sound1.play_sound("small_enemy_shot");
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
		sound1.play_sound("small_enemy_shot");
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
		sound1.play_sound("priest_shot");
	};

	void (*f1)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(2);
		spawn_block1();
		sound1.play_sound("priest");
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
		sound1.play_sound("different_sides_enemy");
	};

	void (*f1)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(2);
		e.shoot("enemy-bullet", Vector2i(25, 25), 12, 0, 90, 4, 3, 8);
		sound1.play_sound("different_sides_enemy");
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
		sound1.play_sound("saw");
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

	e->hit_sound = "boss-hit";

	void (*f1)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(1);
		e.bullet_velocity_mod = 1.f;
		e.shoot("enemy-bullet", Vector2i(25, 25), 18, -25.f, 12.5f, 5, 3, 8);
		e.shoot("saw", Vector2i(50, 50), 59, angle, 0, 1, 3, 8);
		sound1.play_sound("boss-roar");
	};

	void (*f2)(Enemy&) = [](Enemy& e)
	{
		e.call_animation(2);
		e.bullet_velocity_mod = 0.8f;
		e.shoot("enemy-bullet", Vector2i(25, 25), 16, 0, 30.f, 12, 3, 8);
		sound1.play_sound("boss-thunder");
	};

	void (*f3)(Enemy&) = [](Enemy& e)
	{
		float angle = e.angle_to_player();
		e.call_animation(3);
		e.bullet_velocity_mod = 1.2f;
		e.shoot("enemy-bullet", Vector2i(25, 25), 32, angle - 2.5f, 5.f, 2, 3, 8);
		sound1.play_sound("boss-gun");
	};

	void (*f4)(Enemy&) = [](Enemy& e)
	{
		if (random_number(0, 3) == 0)
		{
			e.call_animation(4);
			spawn_block1();
			sound1.play_sound("boss-piano");
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
	font->loadFromFile("../Assets/doves.ttf");
	text[0].setFont(*font);
	text[0].setString("PLAY");
	text[0].setPosition(Vector2f(200u, 200u));
	text[1].setFont(*font);
	text[1].setString("SOUND VOLUME");
	text[1].setPosition(Vector2f(200u, 300u));
	text[2].setFont(*font);
	text[2].setString("MUSIC VOLUME");
	text[2].setPosition(Vector2f(200u, 400u));
	text[3].setFont(*font);
	text[3].setString("GENERAL VOLUMEe");
	text[3].setPosition(Vector2f(200u, 500u));
	text[4].setFont(*font);
	text[4].setString("LEADERBOARD");
	text[4].setPosition(Vector2f(200u, 600u));
	text[5].setFont(*font);
	text[5].setString("EXIT");
	text[5].setPosition(Vector2f(200u, 700u));
	current_position = 0;
	text[current_position].setFillColor(Color::Color(255, 128, 0, 255));
	text1[0].setFont(*font);
	text1[0].setPosition(Vector2f(200u, 800u));
	text1[2].setFont(*font);
	text1[2].setPosition(Vector2f(800u, 800u));
	text1[1].setFont(*font);
	text1[1].setPosition(Vector2f(400u, 800u));
	current_position2 = 2;
	text1[current_position2].setFillColor(Color::Red);

	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
	{
		text[i].setCharacterSize(80);
	}
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
		text[current_position].setFillColor(Color::Color(255, 128, 0, 255));
		sound1.play_sound("change_position");
	}
	else if (current_position == 0)
	{
		text[0].setFillColor(Color::White);
		current_position = NUMBER_OF_ELEMENTS - 1;
		text[current_position].setFillColor(Color::Color(255, 128, 0, 255));
		sound1.play_sound("change_position");
	}
}

void Menu::move_down()
{
	if (current_position + 1 < NUMBER_OF_ELEMENTS)
	{
		text[current_position].setFillColor(Color::White);
		current_position++;
		text[current_position].setFillColor(Color::Color(255, 128, 0, 255));
		sound1.play_sound("change_position");
	}
	else if (current_position == NUMBER_OF_ELEMENTS - 1)
	{
		text[NUMBER_OF_ELEMENTS - 1].setFillColor(Color::White);
		current_position = 0;
		text[current_position].setFillColor(Color::Color(255, 128, 0, 255));
		sound1.play_sound("change_position");
	}
}

void Menu::move_right_to_volume()
{
	text1[0].setFillColor(Color::White);
	current_position2 = 2;
	text1[current_position2].setFillColor(Color::Red);
}

void Menu::move_left_to_volume()
{
	text1[current_position2].setFillColor(Color::White);
	current_position2 = 0;
	text1[current_position2].setFillColor(Color::Red);
}

int MainMenu::Run(RenderWindow& window)
{
	Menu menu;
	bool exit_menu = false;

	sound1.add_sound("hit", "../Assets/Sounds/Hit.wav", 20);
	sound1.add_sound("glass", "../Assets/Sounds/Glass.wav", 29);
	sound1.add_sound("shot", "../Assets/Sounds/normal-shot.wav", 18);
	sound1.add_sound("shot-heavy", "../Assets/Sounds/heavy.wav", 100);
	sound1.add_sound("dodge", "../Assets/Sounds/dodge.wav", 45);
	sound1.add_sound("parry", "../Assets/Sounds/Parry.wav", 65);
	sound1.add_sound("upgrade", "../Assets/Sounds/Buy.wav", 62);
	sound1.add_sound("hit-player", "../Assets/Sounds/player-hit.wav", 70);
	sound1.add_sound("wave-end", "../Assets/Sounds/gong.wav", 86);
	sound1.add_sound("no-ammo", "../Assets/Sounds/no-ammo.wav", 80);
	sound1.add_sound("dodge-ready", "../Assets/Sounds/dodge-ready.wav", 100);
	sound1.add_sound("fat", "../Assets/Sounds/fat.wav", 100);
	sound1.add_sound("saw", "../Assets/Sounds/saw.wav", 50);
	sound1.add_sound("boss-hit", "../Assets/Sounds/boss-hit.wav", 58);
	sound1.add_sound("boss-roar", "../Assets/Sounds/boss-roar.wav", 52);
	sound1.add_sound("boss-thunder", "../Assets/Sounds/boss-thunder.wav", 65);
	sound1.add_sound("boss-gun", "../Assets/Sounds/boss-gun.wav", 55);
	sound1.add_sound("boss-piano", "../Assets/Sounds/boss-piano.wav", 100);
	sound1.add_sound("small_enemy_shot", "../Assets/Sounds/small_enemy_shot.wav", 50);
	sound1.add_sound("buzzing", "../Assets/Sounds/buzzing.wav", 50);
	sound1.add_sound("different_sides_enemy", "../Assets/Sounds/different_sides_enemy.wav", 50);
	sound1.add_sound("priest_shot", "../Assets/Sounds/priest_shot.wav", 50);
	sound1.add_sound("priest", "../Assets/Sounds/priest.wav", 50);
	sound1.add_sound("explosion", "../Assets/Sounds/explosion.wav", 40);
	sound1.add_sound("change_position", "../Assets/Sounds/change_position.wav", 20);
	sound1.add_sound("menu_click", "../Assets/Sounds/menu_click.wav", 50);
	sound1.add_sound("egg", "../Assets/Sounds/egg.wav", 15);

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
					sound1.play_sound("menu_click");
					return 1;
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 1)
				{
					sound1.play_sound("menu_click");
					show_volume_interface = true;
					menu.text1[1].setString(menu.print_string(sound_volume));
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 2)
				{
					sound1.play_sound("menu_click");
					show_volume_interface = true;
					menu.text1[1].setString(menu.print_string(music_volume));
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 3)
				{
					sound1.play_sound("menu_click");
					show_volume_interface = true;
					menu.text1[1].setString(menu.print_string(general_volume));
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 4)
				{
					sound1.play_sound("menu_click");
					return 6;
				}
				if (_event.key.code == Keyboard::Enter && menu.current_position == 5)
				{
					sound1.play_sound("menu_click");
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
						if (_event.key.code == Keyboard::Right && menu.current_position2 == 2)
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
						if (_event.key.code == Keyboard::Left && menu.current_position2 == 0)
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
		window.clear(Color(0, 0, 0, 255));
		menu.print_menu(window);
		if (show_volume_interface)
		{
			window.draw(menu.text1[1]);
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

	_player->hit_sound = "hit-player";

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
	//sound1.add_sound("pogchamp1", "../Assets/Sounds/plantLoud.wav", 100);



	//for (map<string, int>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	//{
	//	cout << i->first << endl;
	//	cout << i->second << endl;
	//	/*i->second = i->second * 0.1;*/
	//	cout << "pog" << endl;
	//}
	/*cout << sound1.volume["no-ammo"];*/
	/*sound1.play_sound("pogchamp");*/
	//sound1.play_sound("pogchamp1");
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
					sound1.play_sound("change_position");
					show_volume_interface = false;
					pause_action_index = 2;
				}
				if (_event.key.code == Keyboard::Up)
				{
					sound1.play_sound("change_position");
					show_volume_interface = false;
					pause_action_index = 3;
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 0)
				{
					sound1.play_sound("menu_click");
					pause_action_index = 4;
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 1)
				{
					sound1.play_sound("menu_click");
					return 2;
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 2)
				{
					sound1.play_sound("menu_click");
					show_volume_interface = true;
					pause_menu.text1[1].setString(pause_menu.print_string(sound_volume));
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 3)
				{
					sound1.play_sound("menu_click");
					show_volume_interface = true;
					pause_menu.text1[1].setString(pause_menu.print_string(music_volume));
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 4)
				{
					sound1.play_sound("menu_click");
					show_volume_interface = true;
					pause_menu.text1[1].setString(pause_menu.print_string(general_volume));
				}
				if (_event.key.code == Keyboard::Enter && pause_menu.current_position == 5)
				{
					sound1.play_sound("menu_click");
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
					if (_event.key.code == Keyboard::Right && pause_menu.current_position2 == 2)
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
					if (_event.key.code == Keyboard::Left && pause_menu.current_position2 == 0)
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

			window.clear(Color(0, 0, 0, 255));
			pause_menu.print_menu(window);
			if (show_volume_interface)
			{
				window.draw(pause_menu.text1[1]);
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
	font1->loadFromFile("../Assets/doves.ttf");
	text[0].setFont(*font1);
	text[0].setString("RESUME");
	text[0].setPosition(Vector2f(200u, 200u));
	text[1].setFont(*font1);
	text[1].setString("RE$TART");
	text[1].setPosition(Vector2f(200u, 300u));
	text[2].setFont(*font1);
	text[2].setString("SOUND VOLUME");
	text[2].setPosition(Vector2f(200u, 400u));
	text[3].setFont(*font1);
	text[3].setString("MUSIC VOLUME");
	text[3].setPosition(Vector2f(200u, 500u));
	text[4].setFont(*font1);
	text[4].setString("GENERAL VOLUME");
	text[4].setPosition(Vector2f(200u, 600u));
	text[5].setFont(*font1);
	text[5].setString("EXIT");
	text[5].setPosition(Vector2f(200u, 700u));
	current_position = 0;

	text[current_position].setFillColor(Color::Color(255, 128, 0, 255));
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
					escape = true;
					return 5;
					//return 0;
				}
				else if (_event.key.code == Keyboard::R)
				{
					escape = false;
					return 5;
					//return 2;
				}
			}
		}
		
		window.clear();
		window.draw(endScreen);
		window.display();
	}

	return -1;
}

SaveResultScreen::SaveResultScreen(int score)
{
	font = new Font();
	font->loadFromFile("../Assets/doves.ttf");
	text.setFont(*font);
	text.setString("");
	text.setPosition(Vector2f(200.f, 400.f));
	text1.setFont(*font);
	text1.setPosition(Vector2f(200.f, 600.f));

}

SaveResultScreen::~SaveResultScreen()
{
	delete font;
}

int SaveResultScreen::Run(RenderWindow& window)
{
	//font = new Font();
	//font->loadFromFile("../Assets/doves.ttf");
	bool typing = true;
	text1.setString("");
	text1.setCharacterSize(50);
	name = "";
	text.setString(to_string(DisplayHP::score) + "$");
	text.setCharacterSize(50);

	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}

			if(_event.type == Event::KeyReleased)
			{
				if (_event.key.code == Keyboard::Enter)
				{
					fstream file;
					file.open("Results.txt", ios::app);
					file << name.toAnsiString() << "   " << DisplayHP::score << ";;" << endl;	//zapisanie wyniku
					file.close();

					if (escape)
					{
						return 0;
					}
					else
					{
						return 2;
					}
					/*typing = false;*/
				}
			}

			if (_event.type == Event::TextEntered && typing)
			{
				if (_event.text.unicode == '\b')
				{
					if(name.getSize() > 0)
					{
						name.erase(name.getSize() - 1, 1);
					}
					//name = myString.substr(0, myString.size() - 1);
				}
				else
				{
					name += _event.text.unicode;
				}
				text1.setString(name);
				/*return 0;*/
			}
		}
		window.clear();
		window.draw(text);
		window.draw(text1);
		window.display();
	}

	return -1;
}

Leaderboard::Leaderboard()
{
	font = new Font();
	font->loadFromFile("../Assets/doves.ttf");
}

Leaderboard::~Leaderboard()
{
	delete font;
}

int Leaderboard::Run(RenderWindow& window)
{
	int size{};
	int size_without_the_last_one{};
	string line;
	/*string name;*/
	string score;
	int typed_name{};
	fstream file1;
	file1.open("Results.txt", ios::in);

	Text texts[5]{};

	while (!file1.eof())	//obliczenie liczby graczy wraz z punktami, konieczne do wypisania rankingu
	{
		getline(file1, line);
		size++;
	}
	size_without_the_last_one = size - 1;	//wskaŸnik jest zawsze ustawiony na nastêpnej pustej linijce, dlatego od rozmiaru nale¿y odj¹æ 1 - wtedy otrzymamy rozmiar zape³nionych linijek
	file1.close();
	if (size_without_the_last_one == 0)	//zabezpieczenie, gdy nie zosta³a rozegrana ¿adna gra
	{
		text.setFont(*font);
		text.setString("No game has been played.");
		text.setCharacterSize(50);
		text.setPosition(Vector2f(200.f, 400.f));
	}
	else
	{
		no_data = false;
		string* table_of_the_names = new string[size_without_the_last_one];	//dynamiczna alokacja pamiêci na podstawie obliczonej wczeœniej liczby gier 
		int* table_of_the_scores = new int[size_without_the_last_one];
		int min{}, first{}, replacement{}, name_replacement{};
		string name_min{}, first_name{};
		fstream file;
		file.open("Results.txt", ios::in);	//wczytywanie z pliku
		for (int i = 0; i < size_without_the_last_one; i++)
		{
			getline(file, line);	//wczytanie pojedynczej linijki zawieraj¹cej imiê i wynik
			for (int j = 0; j < line.length(); j++)
			{
				if (line[j] != 32 && typed_name != 0 && line[j] != ';')	//warunek wykona siê, gdy zmienna typedname zostanie zmodyfikowana po wczeœniejszym wpisaniu spacji - a wiêc bêdzie to element wyniku
					score += line[j];
				if (line[j] != 32 && typed_name == 0)
					name += line[j];
				if (line[j] == 32)	//spacja oznacza koniec imienia
				{
					typed_name++;
					table_of_the_names[i] = name;
				}
				if (line[j] == ';')	//œrednik oznacza koniec wyniku
					table_of_the_scores[i] = stoi(score);
			}
			typed_name = 0;
			score.clear();
			name.clear();
		}
		file.close();
		for (int j = 0; j < size_without_the_last_one; j++)
		{
			name_replacement = j;
			replacement = j;
			min = *(table_of_the_scores + j);
			name_min = *(table_of_the_names + j);
			for (int i = 0; (j + i) < (size_without_the_last_one - 1); i++)
			{
				if (min < *(table_of_the_scores + j + i + 1))
				{
					min = *(table_of_the_scores + j + i + 1);
					replacement = j + i + 1;
					name_min = *(table_of_the_names + j + i + 1);
					name_replacement = j + i + 1;
				}
			}
			first = *(table_of_the_scores + j);
			*(table_of_the_scores + j) = min;
			*(table_of_the_scores + replacement) = first;
			first_name = *(table_of_the_names + j);
			*(table_of_the_names + j) = name_min;
			*(table_of_the_names + name_replacement) = first_name;
		}

		int len = size_without_the_last_one <= 5 ? size_without_the_last_one : 5;

		//if (size_without_the_last_one <= 5)
		//{


		for (int i = 0; i < len; i++)
		{
			texts[i].setFont(*font);
			texts[i].setCharacterSize(50);
			texts[i].setString(to_string(i + 1) + ". " + table_of_the_names[i] + " - " + to_string(table_of_the_scores[i]));
			texts[i].setPosition(Vector2f(200.f, 400.f + i * 100.f));


		}
		//}
		//else
		//{
		//	for (int i = 0; i < 5; i++)
		//	{
		//		text1.setFont(*font);
		//		text1.setString(to_string(i + 1) + ". " + table_of_the_names[i] + " - " + to_string(table_of_the_scores[i]));
		//		text1.setPosition(Vector2f(200.f + i * 200.f, 400.f));
		//	}
		//}
		delete[size_without_the_last_one] table_of_the_scores;
		delete[size_without_the_last_one] table_of_the_names;
	}

	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
			if (_event.key.code == Keyboard::Escape)
			{
				return 0;
			}

		}
		window.clear();
		if (no_data)
			window.draw(text);
		//window.draw(text1);

		for(int i = 0; i < 5; i++)
		{
			window.draw(texts[i]);
		}

		window.display();
	}
	
	return -1;
}