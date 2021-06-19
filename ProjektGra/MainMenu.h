#pragma once
#include"Classes.h"
#include"KeyAction.h"
#include "SetVolume.h"
#include<iostream>
#include<cstdlib>

#define NUMBER_OF_ELEMENTS 6

class cScreen
{
public:
	virtual int Run(RenderWindow& window) = 0;
};

class MainMenu : public cScreen
{
public:
	virtual int Run(RenderWindow& window);
	MainMenu();
	~MainMenu();
};

class Menu //: public cScreen
{
private:
	Font* font;
public:
	Menu();
	~Menu();
	/*virtual int Run(RenderWindow& window);*/
	void print_menu(RenderWindow& window);
	void move_up();
	void move_down();
	void move_right_to_volume();
	void move_left_to_volume();
	string print_string(int volume);
	int current_position;
	int current_position2;
	Text text[NUMBER_OF_ELEMENTS]{};
	Text text1[3];
};

class Game :public cScreen
{
public:
	Game();
	~Game();
	static void spawn_fly();
	static void spawn_fatman();
	static void spawn_block1();
	static void spawn_block2();
	static void spawn_block3();
	static void spawn_block4();
	static void spawn_priest();
	static void spawn_prince();
	static void spawn_sniper();
	static void spawn_boss();

	virtual int Run(RenderWindow& window);

private:
	static float random_dir();
};


//class MainMenu // <--------------------------------------------------------
//{
//public:
//	MainMenu(int screen_size_x, int screen_size_y);
//	MainMenu();
//	~MainMenu();
//	void print_menu(RenderWindow& window);
//	void move_up();
//	void move_down();
//	int current_position;
//	Text text[NUMBER_OF_ELEMENTS]{};
//private:
//	Font* font;
//};

class PauseMenu: public Menu
{
public:
	PauseMenu();
	virtual ~PauseMenu();
	/*virtual int Run(RenderWindow& window);*/
private:
	Font* font1;
};

class Restart : public cScreen
{
public:
	Restart();
	virtual ~Restart();

	virtual int Run(RenderWindow& window);
};

class EndScreen : public cScreen
{
private:
	string screen_key;

public:
	EndScreen(string);
	virtual ~EndScreen();

	virtual int Run(RenderWindow& window);
};

