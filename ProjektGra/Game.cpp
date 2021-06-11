#include"Classes.h"
#include"KeyAction.h"
#include<iostream>

//Player& player = Player();

int main()
{
	print("start");

	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	// wczytanie tekstur gracza i stworzenie jego obiektu
	Texture t, t1, t2;
	t.loadFromFile("../Assets/Player-Spritesheet.png");
	t1.loadFromFile("../Assets/Enemy-Fly.png");
	t2.loadFromFile("../Assets/Player-Projectile.png");


	std::unique_ptr<Player> _player = make_unique<Player>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 375), generate_sprite(&t, Vector2f(50.f, 50.f)), false, Vector2i(100, 100));

	_player->animations.push_back(new AnimationClip(0, 4, 10, *_player, true));
	_player->animations.push_back(new AnimationClip(5, 4, 18, *_player, false));

	_player->create_collider(Vector2f(0.f, 14.f), Vector2f(36.f, 40.f));

	_player->textures.push_back(new Texture(t2));

	//_player->start();

	Engine::objects.push_back(std::move(_player));
	//player = *_player;

	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(&t1, Vector2f(62.f, 62.f)), true, Vector2i(125, 125));

	e->animations.push_back(new AnimationClip(0, 4, 10, *e, true));
	e->animations.push_back(new AnimationClip(6, 3, 16, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->textures.push_back(new Texture(t2));

	e->set_move(Vector2f(1.f, -0.25f), 2.5f, 1, true);

	void (*f)(Enemy&) = [](Enemy& e)
	{	float angle = e.angle_to_player();
		e.shoot(0, Vector2i(25, 50), 10, angle, 0, 1);
		print(to_string(angle));
	};

	e->attacks.push_back(f);
	
	AttackTimer* at1 = new AttackTimer(1.f, *e);

	//e->start();

	Engine::objects.push_back(std::move(e));
	

	// inicjalizacja dodatkowych komponentów
	InputHandler input(dynamic_cast<Player*>(Engine::objects[0].get()));
	Engine engine(&window);
	// inicjalizacja zmiennych do kalkulowania czasu miêdzy klatkami
	Clock clock;
	float _frame_time = clock.getElapsedTime().asSeconds();

	//sound1.add_sound("pogchamp", "../Assets/Sounds/Soundtrack.wav", 20);

	//sound1.play_sound("pogchamp");
	/*BackgroundMusic background;*/

	window.setFramerateLimit(60);
	// pêtla programu
	while (window.isOpen())
	{
		// sprawdzenie zdarzeñ okna
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