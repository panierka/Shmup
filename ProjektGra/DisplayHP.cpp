#include "DisplayHP.h"
#include "Classes.h"

DisplayHP::DisplayHP()
{
	font = new Font();
	health_text = new Text();
	dodge_text = new Text();

	font->loadFromFile("../Assets/arial.ttf");
	health_text->setFont(*font);
	health_text->setString("Wielki Pan Rektor");
	health_text->setCharacterSize(30);
	health_text->setFillColor(Color::Red);

	dodge_text->setFont(*font);
	dodge_text->setString("Wielki Pan Rektor");
	dodge_text->setCharacterSize(30);
	dodge_text->setFillColor(Color::White);

	set_percentage(876.f / 1099.f, DisplayHP::health_text);

	health_text->setPosition(SCREEN_SIZE.x + 40.f, SCREEN_SIZE.y - 100.f);
	dodge_text->setPosition(SCREEN_SIZE.x + 40.f, SCREEN_SIZE.y - 200.f);
}

DisplayHP::~DisplayHP()
{
	delete font;
	delete health_text;
}

void DisplayHP::set_percentage(float p, Text* _text)
{
	int i = round(p * 100);

	_text->setString(to_string(i) + "%");
}

DisplayHP playerhp{};

Font* DisplayHP::font{};
Text* DisplayHP::health_text{};
Text* DisplayHP::dodge_text{};