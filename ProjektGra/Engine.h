#pragma once
//#include<SFML/Graphics.hpp>
#include"Classes.h"

using namespace sf;

class Engine;
class GameObject;
class PhysicalObject;

class Engine
{
public:
	static std::vector<GameObject*> objects;
	static std::vector<PhysicalObject*> phy_objects;
	
private:
	RenderWindow* window;

public:
	Engine(RenderWindow*);

	void update(float);
};

