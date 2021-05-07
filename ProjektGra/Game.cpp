#include"Classes.h"


Sprite* pre_kolo;
Color* colors;

void test()
{
	pre_kolo->setColor(colors[random_number(0, 5)]);
}

void test_r()
{
	pre_kolo->rotate(0.05f);
}

#pragma region > Controls <

	


	void controls_handle()
	{
		
	}


#pragma endregion


int main()
{
	print("start");

	RenderWindow window(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "POG");

	Texture t;
	t.loadFromFile("../Assets/trollge.jpg");

	pre_kolo = generate_sprite(&t);
	GameObject g((Vector2f)SCREEN_SIZE / 2.f + Vector2f(0, 900), pre_kolo, true);

	//kolo.setOrigin(Vector2f(250, 50));
	pre_kolo->setColor(Color::White);
	//pre_kolo->setPosition((Vector2f)SCREEN_SIZE / 2.f);
	
	Timer timer(5.f, test, true);

	//Timer timer1(TIME_PER_FRAME, test_r, true);

	colors = new Color[6]
	{
		Color::Red,
		Color::Green,
		Color::Blue,
		Color::Yellow,
		Color::Magenta,
		Color::Cyan
	};

	g.SetMove(Vector2f(0, 0.5f) * 100.f, 10);

	while (window.isOpen())
	{
		Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		window.draw(*g.sprite);
		window.display();
		
		g.ExecuteMove();
		tick_timers();

		sleep(seconds(TIME_PER_FRAME));
	}
}