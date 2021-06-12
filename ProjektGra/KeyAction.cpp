#include "KeyAction.h"
#include<iostream>

// prêdkoœæ gracza wyra¿ona w jednostkach gry na sekundê
const float PLAYER_SPEED = 6.5f;

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

	player->set_move(next_move, PLAYER_SPEED, 1.f);
}

InputHandler::InputHandler(Player* _player)
{ 
	player = _player;
	
	player->inv_frames = new PlayerInvFrames();
	player->inv_charger = new InvFramesCharger();
	
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
			if (player->ready_to_action)
			{
				if (player->try_use_ammo())
				{
					player->call_animation(1);
					player->shoot("player-bullet", Vector2i(25, 50), player->stat_damage, 0, 0, 1, 4, 24);
				}
				else
				{
					// dŸwiêk
				}
			}
		}));

	defined_actions.push_back(new KeyAction(Keyboard::L, false, []()
		{
			if (player->ready_to_action)
			{
				if (player->try_use_ammo())
				{
					player->call_animation(1);

					int bonus_damage = 0;

					while (player->try_use_ammo())
					{
						bonus_damage += player->stat_damage / 8;
					}

					for (int i = -2; i < 2; i++)
					{
						float _angle = i * 7.5f + random_number(0, 8);

						player->bullet_velocity_mod = player->stat_bullet_velocity * random_number(80, 120) / 100.f;

						player->shoot("player-bullet", Vector2i(25, 50), player->stat_damage_special + bonus_damage, _angle, 0, 1, 4, 24);
					}

					for (int i = 0; i < 2; i++)
					{
						float _angle = random_number(-40, 40);

						player->bullet_velocity_mod = player->stat_bullet_velocity * random_number(70, 130) / 100.f;

						player->shoot("player-bullet", Vector2i(25, 50), player->stat_damage_special + bonus_damage, _angle, 0, 1, 4, 24);
					}

					player->bullet_velocity_mod = player->stat_bullet_velocity;
				}
				else
				{
					// dŸwiêk
				}
			}
		}));
	
	defined_actions.push_back(new KeyAction(Keyboard::Space, false, []()
		{
			if (player->ready_to_action && player->inv_charger->fully_charged)
			{
				player->reload();

				player->call_animation(2);
				player->invulnerable = true;

				player->inv_frames->timer->start();
				player->inv_charger->fully_charged = false;
				player->inv_charger->timer->start(); 
			}
		}));
}

InputHandler::~InputHandler()
{
	
}
