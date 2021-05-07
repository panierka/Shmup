#include"Classes.h"


CircleShape kolo(50.0f);
Color* colors;

void test()
{
	kolo.setFillColor(colors[random_number(0, 5)]);
}

int main()
{
	print("start");
	RenderWindow window(VideoMode(200, 200), "POG");
	kolo.setOrigin(Vector2f(50, 50));
	kolo.setFillColor(Color::Red);
	kolo.setPosition(Vector2f(100, 100));
	
	Timer timer(2.5f, test, true);

	colors = new Color[6]
	{
		Color::Red,
		Color::Green,
		Color::Blue,
		Color::Yellow,
		Color::Magenta,
		Color::Cyan
	};

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
		window.draw(kolo);
		window.display();

		timer.tick();

		sleep(seconds(TIME_PER_FRAME));
	}
}