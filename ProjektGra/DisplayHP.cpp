#include "DisplayHP.h"

DisplayHP::DisplayHP()
{
	font = new Font();
	text = new Text();

	font->loadFromFile("../Assets/arial.ttf");
	text->setFont(*font);
	text->setString("Wielki Pan Rektor");
	text->setCharacterSize(30);
	text->setFillColor(Color::Red);
}

DisplayHP::~DisplayHP()
{
	delete font;
	delete text;
}

DisplayHP playerhp{};