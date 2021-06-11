#pragma once

#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;

class DisplayHP
{
public:
	static Font* font;
	static Text* text;

public:
	DisplayHP();
	~DisplayHP();

	static void set_percentage(float p);
};

extern DisplayHP playerhp;