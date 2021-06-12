#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define NUMBER_OF_ELEMENTS 3
class MainMenu
{
public:
	MainMenu(int screen_size_x, int screen_size_y);
	~MainMenu();
	void print_menu(RenderWindow& window);
	void move_up();
	void move_down();
private:
	Font* font;
	Text text[NUMBER_OF_ELEMENTS]{};
	int current_position;
};