#pragma once
#include<SFML/Window.hpp>
#include"Classes.h"

class Player;

// klasa, kt�rej celem jest sprawdzenie zachowa� dla naci�ni�cia/trzymania danego klawisza
class KeyAction
{
public:
	virtual void Perform();

private:
	void (*action)();
	sf::Keyboard::Key key;
	bool can_be_held;
	bool pressed;

public:

	KeyAction(sf::Keyboard::Key, bool _hold, void (*f)());
	~KeyAction();
};

// klasa obs�uguj�ca wprowadzanie ruch�w przez gracza
class InputHandler
{
public:
	static Player* player;

private:
	std::vector<KeyAction*> defined_actions;

	// nast�pne poruszenie si� prawo/lewo
	static sf::Vector2f next_move;

public:

	InputHandler(Player*);
	~InputHandler();


	void check_input();

};

