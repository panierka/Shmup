#include "DisplayHP.h"
#include "Classes.h"

DisplayHP::DisplayHP()
{
	font = new Font();
	health_text = create_text(100.f);
	dodge_text = create_text(200.f);
	ammo_text = create_text(300.f);
	wave_text = create_text(700.f);
	score_text = create_text(800.f);

	font->loadFromFile("../Assets/arial.ttf");

	health_text->setFillColor(Color::Red);

	add_score(-score);
	score = 0;
}

DisplayHP::~DisplayHP()
{
	delete font;

	delete health_text;
	delete dodge_text;
	delete ammo_text;
	delete wave_text;

	delete score_text;
}

Text* DisplayHP::create_text(float _pos_y)
{
	Text* _text = new Text();

	_text->setFont(*font);
	_text->setString("...");
	_text->setCharacterSize(30);
	_text->setFillColor(Color::White);

	_text->setPosition(SCREEN_SIZE.x + 40.f, SCREEN_SIZE.y - _pos_y);

	return _text;
}

void DisplayHP::set_percentage(float p, Text* _text)
{
	int i = round(p * 100);

	_text->setString(to_string(i) + "%");
}

void DisplayHP::set_count(int _current, int _max, Text* _text)
{
	_text->setString(to_string(_current) + "/" + to_string(_max));
}

void DisplayHP::add_score(int _amount)
{
	score += _amount;
	
	if (score < 0)
	{
		score = 0;
	}

	score_text->setString(to_string(score));
}

Font* DisplayHP::font{};

Text* DisplayHP::health_text{};
Text* DisplayHP::dodge_text{};

Text* DisplayHP::ammo_text{};
Text* DisplayHP::wave_text{};

Text* DisplayHP::score_text{};
int DisplayHP::score = 0;