#include "KeyAction.h"
#include<iostream>


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

	player->set_move(next_move, player->stat_speed, 1.f);
}

// tutaj zostaj¹ dodane poprzez lambdy akcje do wykonania po naciœniêciu/przytrzymaniu danych przycisków
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
					sound1.play_sound("shot");
					DisplayHP::add_score(-player->stat_damage);
					player->bullet_velocity_mod = player->stat_bullet_velocity;
					player->call_animation(1);
					player->shoot("player-bullet", Vector2i(25, 50), player->stat_damage, 0, 0, 1, 4, 24);
				}
				else
				{
					sound1.play_sound("no-ammo");
				}
			}
		}));

	defined_actions.push_back(new KeyAction(Keyboard::L, false, []()
		{
			if (player->ready_to_action)
			{
				if (player->try_use_ammo())
				{
					sound1.play_sound("shot-heavy");
					DisplayHP::add_score(-player->stat_damage);
					player->call_animation(1);

					int bonus_damage = 0;

					// im wiêcej amunicji zosa³o, tym wiêcej obra¿eñ zada ka¿dy pocisk
					while (player->try_use_ammo())
					{
						bonus_damage += player->stat_damage / 6;
					}

					// losowanie kierunków pocisków

					for (int i = -2; i <= 2; i++)
					{
						float _angle = i * 6.5f + random_number(-8, 8);

						player->bullet_velocity_mod = player->stat_bullet_velocity * random_number(80, 120) / 100.f;

						player->shoot("player-bullet2", Vector2i(25, 25), player->stat_damage_special + bonus_damage, _angle, 0, 1, 4, 24);
					}

					for (int i = 0; i < 2; i++)
					{
						float _angle = random_number(-40, 40);

						player->bullet_velocity_mod = player->stat_bullet_velocity * random_number(70, 130) / 100.f;

						player->shoot("player-bullet2", Vector2i(25, 25), player->stat_damage_special + bonus_damage, _angle, 0, 1, 4, 16);
					}

					player->bullet_velocity_mod = player->stat_bullet_velocity;
				}
				else
				{
					sound1.play_sound("no-ammo");
				}
			}
		}));
	
	defined_actions.push_back(new KeyAction(Keyboard::Space, false, []()
		{
			if (player->ready_to_action && player->inv_charger->fully_charged)
			{
				sound1.play_sound("dodge");
				player->reload();

				player->call_animation(2);
				player->invulnerable = true;

				player->inv_frames->timer->start();
				player->inv_charger->fully_charged = false;
				player->inv_charger->timer->start(); 
			}
		}));

	// przydatne miêdzy falami
	defined_actions.push_back(new KeyAction(Keyboard::Enter, false, []()
		{
			waves.check_upgrade();
		}));
}

InputHandler::~InputHandler()
{
	
}
