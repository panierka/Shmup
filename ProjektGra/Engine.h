#pragma once
//#include<SFML/Graphics.hpp>
#include"Classes.h"

using namespace sf;

class Engine;
class GameObject;
class PhysicalObject;
enum Stat : int;

class Engine
{
public:
	// wszystkie obiekty obj�te "symulacj�"
	static std::vector<std::unique_ptr<PhysicalObject>> objects;
	static Shader shader;

	// obs�uga grafik ulepsze�
	static std::vector<std::unique_ptr<Sprite>> stat_upgrades;
	
private:
	RenderWindow* window;

	// komponenty graficzne UI

	Sprite* background;
	Sprite* line1;
	Sprite* line2;
	std::unique_ptr<RectangleShape> rectangle;

public:
	Engine(RenderWindow*);
	~Engine();

	// wybranie ulepsze�
	static void set_stat_upgrades(const std::vector<Stat>& _data);

	// p�tla gry
	void update(float);
};

