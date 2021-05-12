#include"Classes.h"

Sprite* test_sprite;
Color* colors;

GameObject* player;

void test() // U
{
	test_sprite->setColor(colors[random_number(0, 5)]);
}

void test_r() // U
{
	test_sprite->rotate(0.05f);
}

//int licznik{}; // U
bool pressed;

void Keyboard1(Event* a, GameObject* b)
{

	if (a->type == Event::KeyPressed)
	{
		if (a->key.code == Keyboard::D)
		{
			b->SetMove(Vector2f(3.f, 0), PLAYER_SPEED, TIME_PER_FRAME);
		}
		if (a->key.code == Keyboard::A)
		{
			b->SetMove(Vector2f(-3.f, 0), PLAYER_SPEED, TIME_PER_FRAME);
		}

		if (a->key.code == Keyboard::P)
		{
			if (!pressed)
			{
				b->SetMove(Vector2f(0, 20.f), 0.5f, TIME_PER_FRAME);
				pressed = true;
			}
		}
	}
	
	if(a->type == Event::KeyReleased)
	{
		if (a->key.code == Keyboard::P)
		{
			pressed = false;
		}
	}
}

int main()
{
	print("start");

	RenderWindow window(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "POG", Style::Titlebar | Style::Close);

	Texture t;
	t.loadFromFile("../Assets/PlayerShip.png");

	player = new GameObject((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 400), generate_sprite(&t), false);

	//test_sprite->setColor(Color::White); // U
	
	//Timer timer(5.f, test, true); // U

	//Timer timer1(TIME_PER_FRAME, test_r, true); // U

	/*Texture t_back;
	t_back.loadFromFile("../Assets/Background.png");
	Sprite background(t_back);*/

	colors = new Color[6]
	{
		Color::Red,
		Color::Green,
		Color::Blue,
		Color::Yellow,
		Color::Magenta,
		Color::Cyan
	};

	//g.SetMove(Vector2f(0, 1.f), 12.f, 10); // U

	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
			Keyboard1(&_event, player);
		}

		window.clear(Color(129, 57, 42, 255));

		window.draw(*player->sprite);
		window.display();
		
		player->ExecuteMove();
		tick_timers();

		sleep(seconds(TIME_PER_FRAME));
	}
}