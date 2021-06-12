#include "MainMenu.h"

MainMenu::MainMenu(int screen_size_x, int screen_size_y)
{
	font = new Font();
	font->loadFromFile("../Assets/arial.ttf");
	text[0].setFont(*font);
	text[0].setString("Play");
	text[0].setPosition(Vector2f(400u, 350u));
	text[1].setFont(*font);
	text[1].setString("Settings");
	text[1].setPosition(Vector2f(400u, 450u));
	text[2].setFont(*font);
	text[2].setString("Exit");
	text[2].setPosition(Vector2f(400u, 550u));
	current_position = 0;
}

MainMenu::~MainMenu()
{
	delete font;
}

void MainMenu::print_menu(RenderWindow& window)
{
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
	{
		window.draw(text[i]);
	}
}

void MainMenu::move_up()
{
	if (current_position > 0)
	{
		text[current_position].setFillColor(Color::White);
		current_position--;
		text[current_position].setFillColor(Color::Red);
	}
}

void MainMenu::move_down()
{
	if (current_position < NUMBER_OF_ELEMENTS)
	{
		text[current_position].setFillColor(Color::White);
		current_position++;
		text[current_position].setFillColor(Color::Red);
	}
}