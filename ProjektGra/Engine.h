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
	static std::vector<std::unique_ptr<PhysicalObject>> objects;
	static Shader shader;

	static std::vector<std::unique_ptr<Sprite>> stat_upgrades;
	
private:
	RenderWindow* window;

	Sprite* background;
	Sprite* line1;
	Sprite* line2;


	std::unique_ptr<RectangleShape> rectangle;

public:
	Engine(RenderWindow*);
	~Engine();

	static void set_stat_upgrades(const std::vector<Stat>& _data);

	void update(float);
};

