#include "DisplayHP.h"
#include "Classes.h"

DisplayHP::DisplayHP()
{
	font = new Font();
	text = new Text();

	font->loadFromFile("../Assets/arial.ttf");
	text->setFont(*font);
	text->setString("Wielki Pan Rektor");
	text->setCharacterSize(30);
	text->setFillColor(Color::Red);

	set_percentage(876.f / 1099.f);

	text->setPosition(SCREEN_SIZE.x + 40.f, SCREEN_SIZE.y - 100.f);
}

DisplayHP::~DisplayHP()
{
	delete font;
	delete text;
}

void DisplayHP::set_percentage(float p)
{
	int i = round(p * 100);
	text->setString(to_string(i) + "%");
}

DisplayHP playerhp{};

Font* DisplayHP::font{};
Text* DisplayHP::text{};