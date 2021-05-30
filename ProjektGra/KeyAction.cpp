#include "KeyAction.h"
#include<iostream>

// prêdkoœæ gracza wyra¿ona w jednostkach gry na sekundê
const float PLAYER_SPEED = 4.85f;

void KeyAction::Perform()
{
	if (!sf::Keyboard::isKeyPressed(key))
	{
		pressed = false;
	}
	else if (sf::Keyboard::isKeyPressed(key) && (can_be_held || !pressed))
	{
		action();
		pressed = true;
	}
}

KeyAction::KeyAction(sf::Keyboard::Key _key, bool _hold, void (*f)()):
	key(_key), action(f), can_be_held(_hold)
{
	
}

KeyAction::~KeyAction()
{
	
}

Vector2f InputHandler::next_move = Vector2f(0, 0);
Player* InputHandler::player = nullptr;


void InputHandler::check_input()
{
	next_move = sf::Vector2f(0, 0);

	for (auto a : defined_actions)
	{
		a->Perform();
	}

	player->SetMove(next_move, PLAYER_SPEED, 1.f);
}

InputHandler::InputHandler(Player* _player)
{ 
	player = _player;

	defined_actions.push_back(new KeyAction(Keyboard::A, true, []()
		{
			next_move += Vector2f(-1, 0);
		}));

	defined_actions.push_back(new KeyAction(Keyboard::D, true, []()
		{
			next_move += Vector2f(1, 0);
		}));

	defined_actions.push_back(new KeyAction(Keyboard::K, false, []()
		{
			player->call_animation(1);
		}));
}

InputHandler::~InputHandler()
{

}
