#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class DisplayHP
{
public:
	static Font* font;

	static Text* health_text;
	static Text* dodge_text;

	static Text* ammo_text;
	static Text* wave_text;

	static Text* score_text;
	static int score;

public:
	DisplayHP();
	~DisplayHP();

	Text* create_text(float _pos_y);

	static void set_percentage(float p, Text* _text);
	static void set_count(int _current, int _max, Text* _text);
	static void add_score(int _amount);
};
