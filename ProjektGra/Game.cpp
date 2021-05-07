#include<iostream>
#include<SFML/Graphics.hpp>

using namespace sf;

int main()
{
	std::cout << "Test" << std::endl;

	std::cout << "Test2" << std::endl;
	std::cout << "Test4" << std::endl;

	RenderWindow window(VideoMode(200, 200), "POG");
	CircleShape kolo(50.0f);
	kolo.setFillColor(Color::Red);

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
	}
}