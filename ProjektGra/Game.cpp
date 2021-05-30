#include"Classes.h"
#include"KeyAction.h"

GameObject* player;

int main()
{
	print("start");

	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	// wczytanie tekstur gracza i stworzenie jego obiektu
	Texture t;
	t.loadFromFile("../Assets/Player.png");
	player = new Player((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 400), generate_sprite(&t), false);


	// inicjalizacja dodatkowych komponent�w
	InputHandler input(player);

	// inicjalizacja zmiennych do kalkulowania czasu mi�dzy klatkami
	Clock clock;
	float _frame_time = clock.getElapsedTime().asSeconds();
	float _dt = 0.01f;
	float _accumulator = 0.f;

	// p�tla programu
	while (window.isOpen())
	{
		// sprawdzenie zdarze� okna
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
		}
		
		// dynamiczne kalkulowanie realnego delta t mi�dzy kolejnymi klatkami z "wyg�adzaniem"
		_frame_time = clock.restart().asSeconds();
		_accumulator += _frame_time;

		while (_accumulator > _dt)
		{
			_accumulator -= _dt;
			_frame_time += _dt;
		}

		// sprawdzenie akcji gracza
		input.check_input();

		// wy�wietlanie poprawnych informacji na ekranie
		window.clear(Color(129, 57, 42, 255));
		window.draw(*player->sprite);
		window.display();

		// wykonanie si� oblicze� czasomierzy i fizyki
		player->ExecuteMove(_frame_time);
		tick_timers(_frame_time);
	}
}