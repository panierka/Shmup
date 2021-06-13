#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


#define NUMBER_OF_ELEMENTS 3
class MainMenu
{
public:
	MainMenu(int screen_size_x, int screen_size_y);
	MainMenu();
	~MainMenu();
	void print_menu(RenderWindow& window);
	void move_up();
	void move_down();
	int current_position;
	Text text[NUMBER_OF_ELEMENTS]{};
private:
	Font* font;
};

class PauseMenu:public MainMenu
{
public:
	PauseMenu(int screen_size_x, int screen_size_y);
	virtual ~PauseMenu();
private:
	Font* font1;
};