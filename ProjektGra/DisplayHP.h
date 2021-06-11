#pragma once

#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;

class DisplayHP
{
public:
	Font* font;
	Text* text;
	DisplayHP();
	~DisplayHP();
};

extern DisplayHP playerhp;