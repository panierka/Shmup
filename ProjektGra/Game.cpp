#include "MainMenu.h"
#include"Classes.h"
#include"KeyAction.h"
#include<iostream>
#include<cstdlib>


WaveSpawner waves{};

int main()
{
	vector<cScreen*>Screens;
	int screen = 0;
	print("start");
	srand(time(0));
	// stworzenie okna gry
	RenderWindow window(VideoMode(SCREEN_SIZE.x + 275u, SCREEN_SIZE.y), "Gra", Style::Titlebar | Style::Close);

	//utworzenie odpowiednich ekran�w i dodanie ich do wektora
	MainMenu main_menu;
	Screens.push_back(&main_menu); // 0
	Game game;
	Screens.push_back(&game); // 1

	Restart restart;
	Screens.push_back(&restart); // 2

	EndScreen game_over("game-over");
	Screens.push_back(&game_over); // 3
	EndScreen win("end");
	Screens.push_back(&win); // 4

	SaveResultScreen save_result_screen(DisplayHP::score);
	Screens.push_back(&save_result_screen); //5

	Leaderboard leaderboard;
	Screens.push_back(&leaderboard); //6
	//kolejno�� dodania ekran�w do wektora jest bardzo istotna - b�dziemy si� odnosi� w p�tli do indeks�w poszczeg�lnych ekran�w w wektorze
	TextureAtlas atlas;
	
	while (screen >= 0) //p�tla wykonuje si� dop�ki kt�ry� z ekran�w nie zwr�ci -1, wtedy program si� ko�czy
	{
		screen = Screens[screen]->Run(window);
	}

	print("koniec");

	return EXIT_SUCCESS;
}
