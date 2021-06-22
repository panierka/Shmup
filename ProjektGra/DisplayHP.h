#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class DisplayHP
{
public:
	static Font* font;

	// statyczne (dla u�atwienia) teksty, do kt�rych dostaj� si� r�ne metody r�nych obiekt�w

	static shared_ptr<Text> health_text;
	static shared_ptr<Text> dodge_text;

	static shared_ptr<Text> ammo_text;
	static shared_ptr<Text> wave_text;

	static shared_ptr<Text> score_text;
	static int score;

public:
	DisplayHP();
	~DisplayHP();

	// pomocnicza funkcja do tworzenia kolejnych wsk do nowych tekst�w
	shared_ptr<Text> create_text(float _pos_y);

	// ustalenie procent�w z formatowaniem x%
	static void set_percentage(float p, shared_ptr<Text> _text);
	// format x/y
	static void set_count(int _current, int _max, shared_ptr<Text> _text);
	// dodanie punkt�w i format x$
	static void add_score(int _amount);
};
