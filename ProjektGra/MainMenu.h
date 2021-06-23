#pragma once
#include"Classes.h"
#include"KeyAction.h"
#include "SetVolume.h"
#include<iostream>
#include<cstdlib>
#include <fstream>

#define NUMBER_OF_ELEMENTS 6

extern bool escape;

//klasa u¿ywana przez program do prze³¹czania ekranów, dziedziczona przez wszystkie ekrany
class cScreen
{
public:
	virtual int Run(RenderWindow& window) = 0;
};

//ekran g³ównego menu
class MainMenu : public cScreen
{
public:
	virtual int Run(RenderWindow& window);
	MainMenu();
	~MainMenu();
};

//klasa menu z wszystkimi cechami
class Menu 
{
private:
	Font* font;
public:
	Menu();
	~Menu();
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

//ekran gry
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

//klasa pauzy dziedzicz¹ca po menu
class PauseMenu: public Menu
{
public:
	PauseMenu();
	virtual ~PauseMenu();
private:
	Font* font1;
};

//restart, po którego aktywowaniu nastêpuje przeniesienie do ekranu gry
class Restart : public cScreen
{
public:
	Restart();
	virtual ~Restart();

	virtual int Run(RenderWindow& window);
};

//ekran koñca gry
class EndScreen : public cScreen
{
private:
	string screen_key;

public:
	EndScreen(string);
	virtual ~EndScreen();

	virtual int Run(RenderWindow& window);
};

//ekran zapisu
class SaveResultScreen : public cScreen
{
private:
	int score;
	Font* font;
	Text text;
	String name;
	Text text1;
	Text text2;
	Text text3;
public:
	SaveResultScreen(int);
	virtual ~SaveResultScreen();
	virtual int Run(RenderWindow& window);
};

//ekran rankingu
class Leaderboard : public cScreen
{
private:
	Font* font;
	Text text;
	Text text1;
	String name;
public:
	Leaderboard();
	virtual ~Leaderboard();
	virtual int Run(RenderWindow& window);
};