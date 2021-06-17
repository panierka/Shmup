#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class DisplayHP
{
public:
	static Font* font;

	static shared_ptr<Text> health_text;
	static shared_ptr<Text> dodge_text;

	static shared_ptr<Text> ammo_text;
	static shared_ptr<Text> wave_text;

	static shared_ptr<Text> score_text;
	static int score;

public:
	DisplayHP();
	~DisplayHP();

	shared_ptr<Text> create_text(float _pos_y);

	static void set_percentage(float p, shared_ptr<Text> _text);
	static void set_count(int _current, int _max, shared_ptr<Text> _text);
	static void add_score(int _amount);
};
