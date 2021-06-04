#include"Classes.h"
#include"KeyAction.h"
#include<iostream>

Player* player;

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
	player = new Player((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 375), generate_sprite(&t, Vector2f(50.f, 50.f)), false, Vector2i(100, 100));

	player->animations.push_back(new AnimationClip(0, 4, 10, player, true));
	player->animations.push_back(new AnimationClip(5, 4, 18, player, false));

	player->create_collider(Vector2f(0.f, 14.f), Vector2f(36.f, 40.f));

	player->textures.push_back(new Texture(t2));

	Enemy* e = new Enemy((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(&t1, Vector2f(62.f, 62.f)), false, Vector2i(125, 125));

	e->animations.push_back(new AnimationClip(0, 4, 10, e, true));
	e->animations.push_back(new AnimationClip(6, 3, 16, e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));


	// inicjalizacja dodatkowych komponentów
	InputHandler input(player);
	Engine engine(&window);

	// inicjalizacja zmiennych do kalkulowania czasu miêdzy klatkami
	Clock clock;
	float _frame_time = clock.getElapsedTime().asSeconds();

	Music music;
	music.openFromFile("../Assets/Sounds/Soundtrack.wav");
	music.setLoop(true);
	music.setVolume(10);
	music.play();
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

	for (std::size_t i = 0; i < Engine::objects.size(); i++)
	{
		delete Engine::objects[i];
	}

	print("");
	print("koniec");

	return EXIT_SUCCESS;
}