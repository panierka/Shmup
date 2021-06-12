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

public:
	DisplayHP();
	~DisplayHP();

	static void set_percentage(float p, Text* _text);
	static void set_count(int _current, int _max, Text* _text);
};

extern DisplayHP playerhp;