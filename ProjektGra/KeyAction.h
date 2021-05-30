#pragma once
#include<SFML/Window.hpp>
#include"Classes.h"

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

class InputHandler
{
private:
	std::vector<KeyAction*> defined_actions;
	Player* player;
	static Vector2f next_move;

public:

	InputHandler(Player*);
	~InputHandler();


	void check_input();

};
