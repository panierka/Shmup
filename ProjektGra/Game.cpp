#include"Classes.h"

Sprite* test_sprite;
Color* colors;

void test()
{
	test_sprite->setColor(colors[random_number(0, 5)]);
}

void test_r()
{
	test_sprite->rotate(0.05f);
}

//int licznik{};
bool pressed;

void Keyboard1(Event* a, GameObject* b)
{

	if (a->type == Event::KeyPressed)
	{
		if (a->key.code == Keyboard::D)
		{
			b->SetMove(Vector2f(3.f, 0), 0.25f, TIME_PER_FRAME);
		}
		if (a->key.code == Keyboard::A)
		{
			b->SetMove(Vector2f(-3.f, 0), 0.25f, TIME_PER_FRAME);
		}

		if (a->key.code == Keyboard::P)
		{
			if (!pressed)
			{
				b->SetMove(Vector2f(0, 20.f), 5.f, TIME_PER_FRAME);
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
	t.loadFromFile("../Assets/trollge.jpg");

	test_sprite = generate_sprite(&t);
	GameObject g((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 900), test_sprite, false);

	test_sprite->setColor(Color::White);
	
	Timer timer(5.f, test, true);

	Timer timer1(TIME_PER_FRAME, test_r, true);

	colors = new Color[6]
	{
		Color::Red,
		Color::Green,
		Color::Blue,
		Color::Yellow,
		Color::Magenta,
		Color::Cyan
	};

	//g.SetMove(Vector2f(0, 1.f), 12.f, 10);

	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
			Keyboard1(&_event, &g);
		}

		window.clear();

		window.draw(*g.sprite);
		window.display();
		
		g.ExecuteMove();
		tick_timers();

		sleep(seconds(TIME_PER_FRAME));
	}
}