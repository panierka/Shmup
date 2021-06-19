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

	font->loadFromFile("../Assets/doves.ttf");

	health_text->setFillColor(Color::Red);

	add_score(-score);
	score = 0;
}

DisplayHP::~DisplayHP()
{
	delete font;
}

shared_ptr<Text> DisplayHP::create_text(float _pos_y)
{
	shared_ptr<Text> _text = make_shared<Text>();

	_text->setFont(*font);
	_text->setString("...");
	_text->setCharacterSize(60);
	_text->setFillColor(Color::White);

	_text->setPosition(SCREEN_SIZE.x + 40.f, SCREEN_SIZE.y - _pos_y);

	return _text;
}

void DisplayHP::set_percentage(float p, shared_ptr<Text> _text)
{
	int i = round(p * 100);

	_text->setString(to_string(i) + "%");
}

void DisplayHP::set_count(int _current, int _max, shared_ptr<Text> _text)
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

	score_text->setString(to_string(score) + "$");
}

Font* DisplayHP::font{};

shared_ptr<Text> DisplayHP::health_text{};
shared_ptr<Text> DisplayHP::dodge_text{};

shared_ptr<Text> DisplayHP::ammo_text{};
shared_ptr<Text> DisplayHP::wave_text{};

shared_ptr<Text> DisplayHP::score_text{};
int DisplayHP::score = 0;