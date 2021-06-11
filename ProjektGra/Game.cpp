#include"Classes.h"
#include"KeyAction.h"
#include<iostream>

//Player& player = Player();

#pragma region > Przeciwnicy  < 

void spawn_fly()
{

}

#pragma endregion


int main()
{
	print("start");

	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	// wczytanie tekstur gracza i stworzenie jego obiektu
	Texture t, t2;
	t.loadFromFile("../Assets/Player.png");
	t2.loadFromFile("../Assets/Player-Projectile.png");

#pragma region > Inicj. Tekstur <

	update_texture_atlas("player", "Player");
	update_texture_atlas("fly", "Fly");
	update_texture_atlas("player-bullet", "Player-Projectile");
	update_texture_atlas("enemy-bullet", "Enemy-Bullet");

#pragma endregion


	std::unique_ptr<Player> _player = make_unique<Player>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 375), generate_sprite(&t, Vector2f(50.f, 50.f)), false, Vector2i(100, 100));

	_player->animations.push_back(new AnimationClip(0, 4, 10, *_player, true));
	_player->animations.push_back(new AnimationClip(5, 4, 18, *_player, false));

	_player->create_collider(Vector2f(0.f, 14.f), Vector2f(36.f, 40.f));

	_player->textures.push_back(new Texture(t2));

	_player->set_max_health(60);

	//_player->start();

	Engine::objects.push_back(std::move(_player));
	//player = *_player;

	Texture t1, t3;

	t1.loadFromFile("../Assets/Fly.png");
	t3.loadFromFile("../Assets/Enemy-Bullet.png");
	
	std::unique_ptr<Enemy> e = make_unique <Enemy>((Vector2f)SCREEN_SIZE / 2.f + Vector2f(100, -375), generate_sprite(&t1, Vector2f(50.f, 50.f)), true, Vector2i(100, 100));

	e->animations.push_back(new AnimationClip(0, 3, 12, *e, true));
	e->animations.push_back(new AnimationClip(4, 2, 10, *e, false));

	e->create_collider(Vector2f(0.f, 0.f), Vector2f(50.f, 50.f));

	e->textures.push_back(new Texture(t3));
	
	e->set_move(Vector2f(1.f, -0.25f), 3.75f, 1, true);
	
	void (*f)(Enemy&) = [](Enemy& e)
	{	float angle = e.angle_to_player();
		e.call_animation(1);
		e.shoot(0, Vector2i(25, 25), 10, angle - 10.f, 20.f, 2, 3, 8);
		print(to_string(angle));
	};
	e->attacks.push_back(f);

	e->bullet_velocity_mod = 0.95f;
	
	e->set_max_health(25);

	AttackTimer* at1 = new AttackTimer(1.f, *e);

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