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
	// wszystkie obiekty objête "symulacj¹"
	static std::vector<std::unique_ptr<PhysicalObject>> objects;
	static Shader shader;

	// obs³uga grafik ulepszeñ
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

	// wybranie ulepszeñ
	static void set_stat_upgrades(const std::vector<Stat>& _data);

	// pêtla gry
	void update(float);
};

