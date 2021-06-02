#include"Classes.h"
#include"KeyAction.h"
#include<iostream>

Player* player;
Player* player1;

void a()
{

}

int main()
{
	print("start");

	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	// wczytanie tekstur gracza i stworzenie jego obiektu
	Texture t, t1;
	t.loadFromFile("../Assets/Player-Spritesheet.png");
	t1.loadFromFile("../Assets/Player.png");
	player = new Player((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 450), generate_sprite(&t), false, Vector2i(100, 100));
	player->animations = new AnimationClip*[2];

	player->animations[0] = new AnimationClip(0, 4, 10, player, true);
	player->animations[1] = new AnimationClip(5, 4, 18, player, false);

	Enemy* e = new Enemy((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, 450), generate_sprite(&t), false, Vector2i(100, 100));

	// inicjalizacja dodatkowych komponentów
	InputHandler input(player);
	Engine engine(&window);

	// inicjalizacja zmiennych do kalkulowania czasu miêdzy klatkami
	Clock clock;
	float _frame_time = clock.getElapsedTime().asSeconds();

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
}