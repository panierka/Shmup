#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(int screen_size_x, int screen_size_y)
{
	font = new Font();
	font->loadFromFile("../Assets/arial.ttf");
	text[0].setFont(*font);
	text[0].setString("Play");
	text[0].setPosition(Vector2f(400u, 350u));
	text[1].setFont(*font);
	text[1].setString("Leaderboard");
	text[1].setPosition(Vector2f(400u, 450u));
	text[2].setFont(*font);
	text[2].setString("Exit");
	text[2].setPosition(Vector2f(400u, 550u));
	current_position = 0;
	text[current_position].setFillColor(Color::Red);
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
	if (current_position  > 0)
	{
		text[current_position].setFillColor(Color::White);
		current_position--;
		text[current_position].setFillColor(Color::Red);
	}
}

void MainMenu::move_down()
{
	if (current_position + 1 < NUMBER_OF_ELEMENTS)
	{
		text[current_position].setFillColor(Color::White);
		current_position++;
		text[current_position].setFillColor(Color::Red);
	}
}

PauseMenu::PauseMenu(int screen_size_x, int screen_size_y):MainMenu()
{
	font1 = new Font();
	font1->loadFromFile("../Assets/arial.ttf");
	text[0].setFont(*font1);
	text[0].setString("Resume");
	text[0].setPosition(Vector2f(400u, 350u));
	text[1].setFont(*font1);
	text[1].setString("Restart");
	text[1].setPosition(Vector2f(400u, 450u));
	text[2].setFont(*font1);
	text[2].setString("Exit");
	text[2].setPosition(Vector2f(400u, 550u));
	current_position = 0;
	text[current_position].setFillColor(Color::Red);
}

PauseMenu::~PauseMenu()
{
	delete font1;
}
